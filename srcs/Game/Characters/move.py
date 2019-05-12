import numpy as np
import random
import sys


class Bot:
    def __init__(self, x, y):
        self.X = x
        self.Y = y
        self.LastDirection = 0
        self.Bomb = True


ACTIONS = {
    'UP':       0,
    'DOWN':     1,
    'LEFT':     2,
    'RIGHT':    3,
    'BOMB':     4,
    'WAIT':     5
}


def get_data(path):
    fd = open(path)
    fd.readline()
    fd.readline()
    map = []
    enemys = []
    lines = fd.readlines()
    y = 0
    bot = 0
    for line in lines:
        tmp = []
        x = 0
        for c in line:
            if c == '\n':
                continue
            if c == '4':
                bot = Bot(x, y)
            elif c == '3':
                b = Bot(x, y)
                enemys.append(b)
            x += 1
            tmp.append(c)
        map.append(tmp)
        y += 1
    return map, bot, enemys


def transoform_map(map):
    tmp = map
    for y in range(len(tmp)):
        for x in range(len(tmp[y])):
            if tmp[y][x] == '5':
                tmp[y][x] = '-1'
                if x > 0 and tmp[y][x - 1] != '1' and tmp[y][x - 1] != '1':
                    tmp[y][x - 1] = '-1'
                if x < len(tmp[y]) - 1 and tmp[y][x + 1] != '1' and tmp[y][x + 1] != '1':
                    tmp[y][x + 1] = '-1'
                if y > 0 and tmp[y - 1][x] != '1' and tmp[y - 1][x] != '2':
                    tmp[y - 1][x] = '-1'
                if y < len(tmp) - 1 and tmp[y + 1][x] != '1' and tmp[y + 1][x] != '1':
                    tmp[y + 1][x] = '-1'

            elif tmp[y][x] != '-1' and tmp[y][x] != '1' and tmp[y][x] != '2':
                tmp[y][x] = '0'
    return tmp


def move(bot, action):
    if action == ACTIONS['UP']:
        bot.Y -= 1
    elif action == ACTIONS['DOWN']:
        bot.Y += 1
    elif action == ACTIONS['RIGHT']:
        bot.X += 1
    elif action == ACTIONS['LEFT']:
        bot.X -= 1


def put_bomb(t_map, pos_x, pos_y):
    t_map[pos_y][pos_x] = '-2'
    if pos_y > 0 and t_map[pos_y - 1][pos_x] != '1' and t_map[pos_y - 1][pos_x] != '2':
        t_map[pos_y - 1][pos_x] = '-1'
    if pos_y < len(t_map) and t_map[pos_y + 1][pos_x] != '1' and t_map[pos_y + 1][pos_x] != '2':
        t_map[pos_y + 1][pos_x] = '-1'
    if pos_x > 0 and t_map[pos_y][pos_x - 1] != '1' and t_map[pos_y][pos_x - 1] != '2':
        t_map[pos_y][pos_x - 1] = '-1'
    if pos_x < len(t_map[pos_y]) and t_map[pos_y][pos_x + 1] != '1' and t_map[pos_y][pos_x + 1] != '2':
        t_map[pos_y][pos_x + 1] = '-1'


def bomb_explosion(t_map):
    for j in range(len(t_map)):
        for i in range(len(t_map[j])):
            if t_map[j][i] == '-2':
                t_map[j][i] = '0'
                if j > 0 and (t_map[j - 1][i] == '-1' or t_map[j - 1][i] == '2'):
                    t_map[j - 1][i] = '0'
                if j < len(t_map) and (t_map[j + 1][i] == '-1' or t_map[j + 1][i] == '2'):
                    t_map[j + 1][i] = '0'
                if i > 0 and (t_map[j][i - 1] == '-1' or t_map[j][i - 1] == '2'):
                    t_map[j][i - 1] = '0'
                if i < len(t_map[j]) and (t_map[j][i + 1] == '-1' or t_map[j][i + 1] == '2'):
                    t_map[j][i + 1] = '0'


def is_danger(t_map, bot):
    if t_map[bot.Y][bot.X] == '-1' or t_map[bot.Y][bot.X] == '-2':
        return True
    return False


def get_distacnce_to_survive(t_map, bot, direction):
    count = 0
    j = bot.Y
    i = bot.X

    if direction == ACTIONS['UP']:
        while j > 0:
            j -= 1
            if t_map[j][i] == '0':
                return count
            count += 1
    elif direction == ACTIONS['DOWN']:
        while j < len(t_map):
            j += 1
            if t_map[j][i] == '0':
                return count
            count += 1
    elif direction == ACTIONS['LEFT']:
        while i > 0:
            i -= 1
            if t_map[j][i] == '0':
                return count
            count += 1
    elif direction == ACTIONS['RIGHT']:
        while i < len(t_map[j]):
            i += 1
            if t_map[j][i] == '0':
                return count
            count += 1
    return 84


def get_out_danger(t_map, bot):
    outs = []
    outs.append(get_distacnce_to_survive(t_map, bot, ACTIONS['UP']))
    outs.append(get_distacnce_to_survive(t_map, bot, ACTIONS['DOWN']))
    outs.append(get_distacnce_to_survive(t_map, bot, ACTIONS['LEFT']))
    outs.append(get_distacnce_to_survive(t_map, bot, ACTIONS['RIGHT']))

    get_min = np.argmin(outs)
    if get_min == 0:
        return ACTIONS['UP']
    if get_min == 1:
            return ACTIONS['DOWN']
    if get_min == 2:
            return ACTIONS['LEFT']
    if get_min == 3:
        return ACTIONS['RIGHT']


def count_block(t_map, bot_x, bot_y):
    count = 0
    if bot_y < len(t_map) and (t_map[bot_y + 1][bot_x] == '2' or t_map[bot_y + 1][bot_x] == '1'):
        count += 1
    if bot_y > 0 and (t_map[bot_y - 1][bot_x] == '2' or t_map[bot_y - 1][bot_x] == '1'):
        count += 1
    if bot_x < len(t_map[bot_y]) and (t_map[bot_y][bot_x + 1] == '2' or t_map[bot_y][bot_x + 1] == '1'):
        count += 1
    if bot_x > 0 and (t_map[bot_y][bot_x - 1] == '2' or t_map[bot_y][bot_x - 1] == '1'):
        count += 1
    return count


def is_moment_for_bomb(t_map, bot):
    if not bot.Bomb:
        return False
    elif count_block(t_map, bot.X, bot.Y) >= 2:
        return True
    else:
        return False


def choose_direction(t_map, bot_x, bot_y):
    direction = []
    if bot_y > 0 and t_map[bot_y - 1][bot_x] == '0':
        direction.append('UP')
    if bot_y < len(t_map) and t_map[bot_y + 1][bot_x] == '0':
        direction.append('DOWN')
    if bot_x < len(t_map[bot_y]) and t_map[bot_y][bot_x + 1] == '0':
        direction.append('RIGHT')
    if bot_x > 0 and t_map[bot_y][bot_x - 1] == '0':
        direction.append('LEFT')
    if len(direction) == 0:
        return ACTIONS['WAIT']
    choice = random.randint(0, len(direction) - 1)
    return ACTIONS[direction[choice]]


map, bot, enemys = get_data(sys.argv[1])
t_map = transoform_map(map)
pos_x = 0
pos_y = 0
direction = 0

for i in range(5):
    print('----------------------------------------------------\n')
    if i % 1 == 0:
        bomb_explosion(t_map)
        bot.Bomb = True
    if not bot.Bomb:
        direction = get_out_danger(t_map, bot)
    elif is_moment_for_bomb(t_map, bot):
        put_bomb(t_map, bot.X, bot.Y)
        print('Bomb Planted')
        direction = ACTIONS['BOMB']
        bot.Bomb = False
    else:
        direction = choose_direction(t_map, bot.X, bot.Y)
    move(bot, direction)
    print('step number =', i, 'direction =', direction)
    print('bot pos = x:', bot.X, 'y:', bot.Y)
    print('enemy pos = x:', pos_x, 'y:', pos_y, '\n')
    for line in t_map:
        print(line)
    bot.LastDirection = direction
