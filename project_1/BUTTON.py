from turtle import done
import pygame

class Button:
    def __init__(self, text,  pos, font, bg="white", feedback=""):
        self.x, self.y = pos
        self.font = pygame.font.SysFont("Arial", font)
        if feedback == "":
            self.feedback = "text"
        else:
            self.feedback = feedback
        self.change_text(text, bg)
        self.opened= False
        self.curr_text=text
        self.text=text
    def change_text(self, text, bg="black"):
            self.curr_text = self.font.render(text, 1, pygame.Color("Black"))
            self.size = self.curr_text.get_size()
            self.surface = pygame.Surface(self.size)
            self.surface.fill(bg)
            self.surface.blit(self.curr_text, (0, 0))
            self.rect = pygame.Rect(self.x, self.y, self.size[0], self.size[1])
    def show(self, screen):
        screen.blit(self.surface, (self.x, self.y))
    def click(self, event):
        x, y = pygame.mouse.get_pos()
        if event.type == pygame.MOUSEBUTTONDOWN:
            if pygame.mouse.get_pressed()[0]:
                if self.rect.collidepoint(x, y):
                    if(not self.opened):
                        self.change_text(self.feedback, bg="pink")

class Show_Button(Button):
    def __init__(self, text,  pos, font, lines, pos_lines, bg="white", feedback=""):
        self.lines=lines
        self.pos_lines_x, self.pos_lines_y=pos_lines
        Button.__init__(self, text,  pos, font, bg, feedback)
        self.opened=False
    def show(self, screen):
        screen.blit(self.surface, (self.x, self.y))
        if self.opened:
            font_for_ask_pet_type=pygame.font.SysFont('arial',24)
            curr_hight=self.pos_lines_y
            arr=[]
            counter=0
            for i in self.lines:
                arr.append(font_for_ask_pet_type.render(i, True, (0,0,0)))
                screen.blit(arr[counter],(self.pos_lines_x,curr_hight))
                curr_hight+=25
                counter+=1
    def click(self,event, screen):
        x, y = pygame.mouse.get_pos()
        if event.type == pygame.MOUSEBUTTONDOWN:
            if pygame.mouse.get_pressed()[0]:
                if self.rect.collidepoint(x, y):
                    print(2)
                    font_for_ask_pet_type=pygame.font.SysFont('arial',24)
                    curr_hight=self.pos_lines_y
                    counter =0
                    arr=[]
                    for i in self.lines:
                        arr.append(font_for_ask_pet_type.render(i, True, (0,0,0)))
                        screen.blit(arr[counter],(self.pos_lines_x,curr_hight))
                        curr_hight+=25
                        counter+=1
                    if (not self.opened):
                        self.change_text(self.feedback, bg="pink")
                    else:
                        self.change_text(self.text, bg="white")
                    self.opened=not self.opened

class Do_Button(Button):
    def __init__(self, text,  pos, font,char, bg="white", feedback=""):
        self.char = char
        Button.__init__(self, text,  pos, font, bg, feedback)
    def click(self, event, pet):
        x, y = pygame.mouse.get_pos()
        if event.type == pygame.MOUSEBUTTONDOWN:
            if pygame.mouse.get_pressed()[0]:
                if self.rect.collidepoint(x, y):
                    if(not self.opened):
                        pet.increase(self.char, self.text)

class Show_Buttons_Button(Show_Button):
    def __init__(self, text, pos, font, lines, pos_lines,char,screen, bg="white", feedback=""):
        self.char=char
        self.screen = screen
        self.arr =[]
        super().__init__(text, pos, font, lines, pos_lines, bg, feedback)
    def show(self, screen):
        screen.blit(self.surface, (self.x, self.y))
        if self.opened:
            curr_hight=self.pos_lines_y
            self.arr=[]
            counter=0
            for i in self.lines:
                self.arr.append(Do_Button(self.lines[counter], (self.pos_lines_x, curr_hight), 24, self.char, "white", "done"))
                self.arr[counter].show(self.screen)
                curr_hight+=30
                counter+=1
    def click(self,event, screen):
        x, y = pygame.mouse.get_pos()
        if event.type == pygame.MOUSEBUTTONDOWN:
            if pygame.mouse.get_pressed()[0]:
                if self.rect.collidepoint(x, y):
                    curr_hight=self.pos_lines_y
                    arr=[]
                    counter=0
                    for i in self.lines:
                        arr.append(Do_Button(self.lines[counter], (self.pos_lines_x, curr_hight), 24, self.char, "white", "done"))
                        arr[counter].show(self.screen)
                        curr_hight+=30
                        counter+=1
                    if (not self.opened):
                        self.change_text(self.feedback, bg="pink")
                    else:
                        self.change_text(self.text, bg="white")
                    self.opened=not self.opened
    def size(self):
        return len(self.arr)