import glfw
from OpenGL.GL import *
from math import ceil
sizeX = 1000
sizeY = 1000
data = [[255] * sizeX for i in range(sizeY)]
points = []
edges = []
cnt = 0

def key_callback(window, key, scancode, action, mods):
    global cnt, data, edges, points
    if key == glfw.KEY_SPACE and action == glfw.PRESS:
        drawLine(points[-1][0], points[-1][1], points[0][0], points[0][1])
        add_point(points[0][0], points[0][1])
    if key == glfw.KEY_1 and action == glfw.PRESS:
        miny = min([y for _, y in points])
        maxy = max([y for _, y in points])
        fill(miny + 1, maxy - 1)
    if key == glfw.KEY_2 and action == glfw.PRESS:
        filtration()

    if key == glfw.KEY_ESCAPE and action == glfw.PRESS:
        glfw.set_window_should_close(window, True)

def mouse_button_callback(window, button, action, mods):
    global cnt, data, edges, points
    if button == glfw.MOUSE_BUTTON_LEFT and action == glfw.PRESS:
        t = list(glfw.get_cursor_pos(window))
        t[0] = int(t[0])
        t[1] = int(-t[1])
        print(f"Ox = {t[0]}, Oy = {t[1]}")
        add_point(t[0], t[1])
        if len(edges) > 0:
            for edge in edges:
                drawLine(points[edge[0]][0], points[edge[0]][1], points[edge[1]][0],  points[edge[1]][1])
            

def add_point(x,y):
    global cnt, points
    points.append((x, y))
    cnt += 1
    add_edge()

def add_edge():
    global cnt, edges
    if cnt > 1:
        if cnt == 3:
            edges.append((0, 1)) 
        edges.append((cnt - 2, cnt - 1))

def drawLine(x0, y0, x1, y1):
    if x0 == x1:
        m = 2 ** 32
    else:
        m = ((y1 - y0) /
             (x1 - x0))
    e = -.5
    x = x0
    y = y0
    isSharp = True
    if x <= x1 and y <= y1:
        if m > 1:
            isSharp = False
            m **= -1
        while x <= x1 and y <= y1:
            data[y][x] = 0
            if isSharp:
                x += 1
            else:
                y += 1
            e += m
            if e >= 0:
                if isSharp:
                    y += 1
                else:
                    x += 1
                e -= 1
    elif x >= x1 and y <= y1:
        m = -m
        if m > 1:
            isSharp = False
            m **= -1
        while x >= x1 and y <= y1:
            data[y][x] = 0
            if isSharp:
                x -= 1
            else:
                y += 1
            e += m
            if e >= 0:
                if isSharp:
                    y += 1
                else:
                    x -= 1
                e -= 1
    elif x >= x1 and y >= y1:
        if m > 1:
            isSharp = False
            m **= -1
        while x >= x1 and y >= y1:
            data[y][x] = 0
            if isSharp:
                x -= 1
            else:
                y -= 1
            e += m
            if e >= 0:
                if isSharp:
                    y -= 1
                else:
                    x -= 1
                e -= 1
    elif x <= x1 and y >= y1:
        m = -m
        if m > 1:
            m **= -1
            isSharp = False
        while x <= x1 and y >= y1:
            data[y][x] = 0
            if isSharp:
                x += 1
            else:
                y -= 1
            e += m
            if e >= 0:
                if isSharp:
                    y -= 1
                else:
                    x += 1
                e -= 1

def filtration():
    global data
    mask = [[1, 2, 1],
            [2, 4, 2],
            [1, 2, 1]]
    for i in range(1, sizeY - 1):
        for j in range(1, sizeX - 1):
            if zeroChek(data, i, j):
                data[i][j] = int(
                    (mask[0][0] * data[i + 1][j - 1] + mask[0][1] * data[i + 1][j] + mask[0][2] * data[i + 1][j + 1] +
                     mask[1][0] * data[i][j - 1]   +   mask[1][1] * data[i][j]   +   mask[1][2] * data[i][j + 1] +
                     mask[2][0] * data[i - 1][j - 1] + mask[2][1] * data[i - 1][j] + mask[2][2] * data[i - 1][j + 1])
                    / 16)
            else:
                data[i][j] = 0
    print("filtration = True")

def zeroChek(data, i, j):
    return 0 < (data[i + 1][j - 1] + data[i + 1][j] + data[i + 1][j + 1] + data[i][j - 1] + data[i][j] + data[i][j + 1]
                + data[i - 1][j - 1] + data[i - 1][j] + data[i - 1][j + 1])

def fill(start, end): 
    global data
    for y in range(start, end):
        active_edge = []

        for edge in edges:
            x1, y1 = points[edge[0]]
            x2, y2 = points[edge[1]]
            if (y1 >= y and y2 <= y) or (y1 <= y and y2 >= y):
                dx = (x2 - x1) / (y2 - y1)
                x = int(ceil(((y - y1) * dx) + x1))
                active_edge.append(x)

        active_edge.sort()
        ind, e1 = 0, 0
        for e2 in active_edge:

            if ind % 2 == 0:
                e1 = e2
            else:
                if e1 == e2:
                    ind += 1
                else:
                    for x in range(e1, e2):
                        if(data[y][x] != 0):
                            data[y][x] = 150
            ind += 1
    print("fill = True")

def display(window):
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    glClearColor(0, 0, 0, 0)
    glRasterPos(-1, -1)
    #glPixelZoom(2, 2)
    glDrawPixels(sizeX, sizeY, GL_LUMINANCE, GL_UNSIGNED_BYTE, data)
    glfw.swap_buffers(window)
    glfw.poll_events()
      
def main():

    if not glfw.init():
        return
    window = glfw.create_window(sizeX, sizeY, "lab_4", None, None)
    if not window:
        glfw.terminate()
        return
    glfw.make_context_current(window)
    glfw.set_key_callback(window, key_callback)
    glfw.set_mouse_button_callback(window, mouse_button_callback)
    while not glfw.window_should_close(window):
        display(window)
    glfw.destroy_window(window)
    glfw.terminate()

if __name__ == '__main__':
    main()