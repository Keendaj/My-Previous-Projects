import pygame
from random import randint
pygame.init()
x = 1000
y = 800
fonh = 0
fonw = 0
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
k = 0
sc = pygame.display.set_mode((x, y))
pygame.display.set_caption("Running Man")
runleft = [pygame.image.load("man_runleft0.png"), pygame.image.load("man_runleft1.png"),
           pygame.image.load("man_runleft2.png")]
runright = [pygame.image.load("man_runright0.png"), pygame.image.load("man_runright1.png"),
            pygame.image.load("man_runright2.png")]
zombieright = [pygame.image.load('zombie_rwalk0.png'), pygame.image.load('zombie_rwalk1.png'),
               pygame.image.load('zombie_rwalk2.png'), pygame.image.load('zombie_rwalk3.png'),
               pygame.image.load('zombie_rwalk4.png'), pygame.image.load('zombie_rwalk5.png'),
               pygame.image.load('zombie_rwalk6.png'), pygame.image.load('zombie_rwalk7.png')]
zombieleft = [pygame.image.load('zombie_lwalk0.png'), pygame.image.load('zombie_lwalk1.png'),
              pygame.image.load('zombie_lwalk2.png'), pygame.image.load('zombie_lwalk3.png'),
              pygame.image.load('zombie_lwalk4.png'), pygame.image.load('zombie_lwalk5.png'),
              pygame.image.load('zombie_lwalk6.png'), pygame.image.load('zombie_lwalk7.png')]
fon = pygame.image.load("Fon.jpg")
idle = pygame.image.load("man_idle.png")
font = pygame.font.SysFont("arial", 50)
font1 = pygame.font.SysFont("arial", 20)
zombie = []
bullet = pygame.image.load('patron.png')
win = font.render("Мои поздравления ты убил их всех!", 1, WHITE)
win1 = font.render("А может и нет...", 1, WHITE)
gameover = font.render("Ты умер пытаясь сбежать от зомби.", 1, RED)
win2 = font.render("Ты смог сбежать из этого места!", 1, WHITE)
win21 = font.render("Но навсегда ли это...", 1, WHITE)
text = font1.render('Твоя задача убить 30 зомби', 1, BLACK)
text1 = font1.render(str(k)+'/30', 1, BLACK)
m = [400, 445]
x = 0
zombiec = []
zombiecd = 5
lastzombietime = 0
zombiespawn = randint(0, 1)
speed = 8
wining = 1
game = 1
clock = pygame.time.Clock()
fps = 60
left = False
right = False
animation = 0
otchet = 0
jumping = False
jump = 11
anz = 0
otz = 0
sc.fill((0, 0, 0))
pylks = pygame.image.load("patron.png")
patrons = []
lastmove = "right"
class patron():
    def __init__(self, x, y, storona, speed):
        self.x = x
        self.y = y
        self.storona = storona
        self.vel = storona*speed
    def drawing(self, sc, bullet):
        sc.blit(bullet, (self.x, self.y))
def DW(H, W):
    global animation
    global otchet
    global text
    global text1
    sc.blit(fon, (H + 1500, W))
    sc.blit(fon, (H + 3000, W))
    sc.blit(fon, (H + 4500, W))
    sc.blit(fon, (H + 6000, W))
    sc.blit(fon, (H + 7500, W))
    sc.blit(fon, (H + 9000, W))
    sc.blit(fon, (H, W))
    sc.blit(idle, (m[0], m[1]))
    sc.blit(text, (10, 20))
    sc.blit(text1, (10, 40))
    animation = 0
    otchet = 0
def DWl(H,W):
    global animation
    global otchet
    global text
    global text1
    sc.blit(fon, (H + 1500, W))
    sc.blit(fon, (H + 3000, W))
    sc.blit(fon, (H + 4500, W))
    sc.blit(fon, (H + 6000, W))
    sc.blit(fon, (H + 7500, W))
    sc.blit(fon, (H + 9000, W))
    sc.blit(fon, (H, W))
    sc.blit(runleft[animation], (m[0], m[1]))
    if animation != 2 and otchet == 4:
        animation += 1
        otchet -= 4
    elif animation == 2 and otchet == 4:
        animation -= 2
        otchet -= 4
    else:
        otchet += 1
    sc.blit(text, (10, 20))
    sc.blit(text1, (10, 40))
def DWr(H, W):
    global animation
    global otchet
    global text
    global text1
    sc.blit(fon, (H + 1500, W))
    sc.blit(fon, (H + 3000, W))
    sc.blit(fon, (H + 4500, W))
    sc.blit(fon, (H + 6000, W))
    sc.blit(fon, (H + 7500, W))
    sc.blit(fon, (H + 9000, W))
    sc.blit(fon, (H, W))
    sc.blit(runright[animation], (m[0], m[1]))
    if animation != 2 and otchet == 6:
        animation += 1
        otchet -= 6
    elif animation == 2 and otchet == 6:
        animation -= 2
        otchet -= 6
    else:
        otchet += 1
    sc.blit(text, (10, 20))
    sc.blit(text1, (10, 40))
while True:
    if game == 1:
        for i in pygame.event.get():
            if i.type == pygame.QUIT:
                exit()
            if i.type == pygame.MOUSEBUTTONDOWN:
                if i.button == 1:
                    if lastmove == 'right':
                        storona = 1
                    elif lastmove == 'left':
                        storona = -1
                    if len(patrons)<6:
                        patrons.append(patron(round(m[0]+150),round(m[1]+200//2), storona, speed))
        for bullet1 in patrons:
            if bullet1.x <= 1000 and bullet1.x >= 0:
                bullet1.x += bullet1.vel
            else:
                patrons.pop(patrons.index(bullet1))
        right = False
        left = False
        keys = pygame.key.get_pressed()
        if keys[pygame.K_LEFT]:
            if fonh<0:
                fonh += speed
                for popan in range(len(zombiec)):
                        zombiec[popan][0] += speed / 4
                right = False
                left = True
            elif fonh == 0:
                for popan in range(len(zombiec)):
                        zombiec[popan][0] += speed / 4
                pass
            lastmove = 'left'
        if keys[pygame.K_RIGHT]:
            speed = 8
            fonh -= speed
            for popan in range(len(zombiec)):
                zombiec[popan][0] -= speed / 4
            left = False
            right = True
            lastmove = 'right'
        if keys[pygame.K_SPACE]:
            if not (jumping):
                jumping = True
        if jumping:
            if jump >= -11:
                if jump < 0:
                    m[1] += (jump ** 2) / 2
                else:
                    m[1] -= (jump ** 2) / 2
                jump -= 1
            else:
                jumping = False
                jump = 11
        currentTime = pygame.time.get_ticks()
        if currentTime - lastzombietime > zombiecd:
            zombiespawn = randint(0, 1)
            if zombiespawn == 0:
                zombiec.append([0, 450])
                zombie.append(zombieright)
            elif zombiespawn == 1:
                zombiec.append([1000, 450])
                zombie.append(zombieleft)
            lastzombietime = currentTime
            zombiecd = randint(300, 3000)

        if left == False and right == False:
            DW(fonh, fonw)
        if left == True and right == False:
            DWl(fonh, fonw)
        if left == False and right == True:
            DWr(fonh, fonw)
        if k >= 30:
            game = 2
            wining = 2
        for popan in range(len(zombiec)):
            if zombiec[popan][0] > m[0]:
                zombiec[popan][0] -= speed/4
                sc.blit(zombie[popan][anz], zombiec[popan])
            elif zombiec[popan][0] < m[0]:
                zombiec[popan][0] += speed/4
                sc.blit(zombie[popan][anz], zombiec[popan])

        for bullet1 in patrons:
            bullet1.drawing(sc, bullet)
        for bullet1 in patrons:
            for popan in range(len(zombiec) - 1):
                if zombiec[popan][0] > m[0]:
                    if zombiec[popan][0] <= bullet1.x + 8:
                       if zombiec[popan][1] <= bullet1.y:
                            patrons.pop(patrons.index(bullet1))
                            del zombiec[popan]
                            del zombie[popan]
                            int(k)
                            k += 1
        for bullet1 in patrons:
            for popan in range(len(zombiec) - 1):
                if zombiec[popan][0] < m[0]:
                    if zombiec[popan][0] >= bullet1.x - 150:
                        if zombiec[popan][1] <= bullet1.y:
                            patrons.pop(patrons.index(bullet1))
                            del zombiec[popan]
                            del zombie[popan]
                            int(k)
                            k += 1
        if anz != 2 and otz == 4:
            anz += 1
            otz -= 4
        elif anz == 2 and otz == 4:
            anz -= 2
            otz -= 4
        else:
            otz += 1
        for popan in range(len(zombiec) - 1):
            if zombiec[popan][0] > m[0]:
                if zombiec[popan][0] <= m[0]+100:
                    game = 2
            elif zombiec[popan][0] < m[0]:
                if zombiec[popan][0] >= m[0]-100:
                    game = 2
        if fonh <= -9500:
            game = 2
            wining = 3
        text1 = font1.render(str(k) + '/30', 1, BLACK)
        pygame.display.update()
        clock.tick(fps)
    elif game == 2:
        sc.fill(BLACK)
        if wining == 2:
            sc.blit(win, (200, 350))
            sc.blit(win1, (200, 400))
        elif wining == 3:
            sc.blit(win, (200, 350))
            sc.blit(win1, (200, 400))
        else:
            sc.blit(gameover, (200, 400))
        pygame.display.update()
        clock.tick(fps)