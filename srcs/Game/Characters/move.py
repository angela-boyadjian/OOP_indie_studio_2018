import sys


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


DIRECTIONS = {
    'UP': 0,
    'DOWN': 1,
    'LEFT': 2,
    'RIGHT': 3,
    'WAIT': 4,
    'BOMB': 5
}


class Bot:
    def __init__(self, x, y):
        self.X = x
        self.Y = y
        self.putBomb = False


def find_shortest_enemy(enemys, bot):
    dif = []
    for enemy in enemys:
        dif.append([enemy.X - bot.X, enemy.Y - bot.Y])
        if dif[-1][0] < 0:
            dif[-1][0] *= -1
        if dif[-1][1] < 0:
            dif[-1][1] *= -1
    dif_X = dif[0][0]
    dif_Y = dif[0][1]
    dif.pop()
    for d in dif:
        if d[0] < dif_X and d[1] < dif_Y:
            dif_X = d[0]
            dif_Y = d[1]
    return dif_X, dif_Y


def is_in_danger(map, x, y):
    if map[y][x] == '-1':
        return True
    else:
        return False


def get_out_danger(map, x, y):
    if x > 0 and map[y][x - 1] == '0':
        return DIRECTIONS['LEFT']
    elif x < len(map[y]) and map[y][x + 1] == '0':
        return DIRECTIONS['RIGHT']
    elif y > 0 and map[y - 1][x] == '0':
        return DIRECTIONS['UP']
    elif y < len(map) and map[y + 1][x] == '0':
        return DIRECTIONS['DOWN']
    else:
        return DIRECTIONS['UP']


def get_direction_to_shortest_enemy(bot, enemy_x, enemy_y):
    dif_X = bot.X - enemy_x
    dif_Y = bot.Y - enemy_y
    if dif_X < 0:
        dif_X *= -1
    if dif_Y < 0:
        dif_Y *= -1
    if dif_X > dif_Y:
        if bot.X < enemy_x:
            return DIRECTIONS['RIGHT']
        else:
            return DIRECTIONS['LEFT']
    else:
        if bot.Y < enemy_y:
            return DIRECTIONS['DOWN']
        else:
            return DIRECTIONS['UP']


def go_to_shortest_enemy(t_map, bot, enemy_x, enemy_y):
    direction = get_direction_to_shortest_enemy(bot, enemy_x, enemy_y)
    if direction == DIRECTIONS['RIGHT']:
        if t_map[bot.Y][bot.X + 1] == '2':
            return DIRECTIONS['BOMB']
    elif direction == DIRECTIONS['LEFT']:
        if t_map[bot.Y][bot.X - 1] == '2':
            return DIRECTIONS['BOMB']
    elif direction == DIRECTIONS['UP']:
        if t_map[bot.Y - 1][bot.X] == '2':
            return DIRECTIONS['BOMB']
    else:
        if t_map[bot.Y + 1][bot.X] == '2':
            return DIRECTIONS['BOMB']
    return direction


def choose_direction(t_map, bot):
    if is_in_danger(t_map, bot.X, bot.Y):
        return get_out_danger(t_map, bot.X, bot.Y)
    return DIRECTIONS['WAIT']


def move(bot, direction):
    if direction == DIRECTIONS['UP']:
        bot.Y -= 1
    elif direction == DIRECTIONS['DOWN']:
        bot.Y += 1
    elif direction == DIRECTIONS['RIGHT']:
        bot.X += 1
    elif direction == DIRECTIONS['LEFT']:
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


map, bot, enemys = get_data(sys.argv[1])
t_map = transoform_map(map)
pos_x = 0
pos_y = 0

for i in range(10):
    print('----------------------------------------------------\n')
    direction = choose_direction(t_map, bot)
    if direction != DIRECTIONS['WAIT']:
        move(bot, direction)
    else:
        if bot.putBomb:
            bomb_explosion(t_map)
            bot.putBomb = False
        else:
            pos_x, pos_y = find_shortest_enemy(enemys, bot)
            direction = go_to_shortest_enemy(t_map, bot, pos_x, pos_y)
            if direction == DIRECTIONS['BOMB']:
                print('\nBomb Planted')
                bot.putBomb = True
                put_bomb(t_map, bot.X, bot.Y)
                direction = choose_direction(t_map, bot)
            move(bot, direction)
    print('step number ', i, direction)
    print('bot pos = x:', bot.X, 'y:', bot.Y)
    print('enemy pos = x:', pos_x, 'y:', pos_y, '\n')
    for line in t_map:
        print(line)
