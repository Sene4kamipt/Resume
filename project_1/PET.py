import time
import pygame
from BUTTON import Button

class PET:
    def __init__(self, type, name, screen):
        self.type= type
        self.name = name
        self.screen = screen
        if (type == "DOG"):
            self.image = pygame.image.load('dog.jpg')
        else:
            self.image = pygame.image.load('cat.jpg')
        self.rect= self.image.get_rect()
        self.screen_rect = screen.get_rect()
        self.rect.centerx = self.screen_rect.centerx
        self.rect.bottom = self.screen_rect.bottom-100
        self.feed = 10
        self.image_feed = pygame.image.load('meet.jpg')
        self.feed_x=20
        self.feed_y=30
        self.clean = 10
        self.image_clean = pygame.image.load('shower.jpg')
        self.clean_x=20
        self.clean_y=60
        self.drink = 10
        self.image_drink = pygame.image.load('drop.jpg')
        self.drink_x=20
        self.drink_y=90
        self.happy = 10
        self.image_happy = pygame.image.load('heart.jpg')
        self.happy_x=20
        self.happy_y=120
        self.time_creation_clean = time.time()
        self.time_creation_feed = time.time()
        self.time_creation_drink = time.time()
        self.time_creation_happy = time.time()
    def draw(self):
        self.screen.blit(self.image, self.rect)
        #self.screen.blit(self.image_feed, self.rect_feed)
        for i in range(self.feed):
            self.screen.blit(self.image_feed, (self.feed_x,self.feed_y))
            self.feed_x+=20
        self.feed_x=20
        for i in range(self.clean):
            self.screen.blit(self.image_clean, (self.clean_x,self.clean_y))
            self.clean_x+=20
        self.clean_x=20
        for i in range(self.drink):
            self.screen.blit(self.image_drink, (self.drink_x,self.drink_y))
            self.drink_x+=20
        self.drink_x=20
        for i in range(self.happy):
            self.screen.blit(self.image_happy, (self.happy_x,self.happy_y))
            self.happy_x+=20
        self.happy_x=20
    def time_create_clean(self):
        return self.time_creation_clean
    def time_create_feed(self):
        return self.time_creation_feed
    def time_create_drink(self):
        return self.time_creation_drink
    def time_create_happy(self):
        return self.time_creation_happy
    def time_create_feed_plus(self):
        self.time_creation_feed+=10
    def time_create_clean_plus(self):
        self.time_creation_clean+=20
    def time_create_drink_plus(self):
        self.time_creation_drink+=5
    def time_create_happy_plus(self):
        self.time_creation_happy+=30
    def increase(self, char, component):
        if char == "clean":
            self.clean+=1
            if self.clean>10:
                self.clean=10
        if char == "feed":
            self.feed+=1
            if self.feed>10:
                self.feed=10
        if char == "drink":
            self.drink+=1
            if self.drink>10:
                self.drink=10
        if char == "happy":
            self.happy+=1
            if self.happy>10:
                self.happy=10

class Dog(PET):
    def __init__(self, type, name, screen):
        super().__init__(type, name, screen)
    def increase(self, char, component):
        if char == "clean":
            if component == "bath":
                self.clean+=3
                self.happy+=1
            if component == "shower":
                self.clean+=2
                self.happy+=1
            if component == "bucket":
                self.clean+=1
                self.happy-=1
            if self.clean>10:
                self.clean=10
            if self.feed>10:
                self.feed=10
            if self.happy>10:
                self.happy=10
        if char == "feed":
            #"meet", "vegetables", "dry food", "fish", "honey"
            if component=="meet":
                self.feed+=3
                self.happy+=1
                self.drink-=1
                self.clean-=1
            if component == "vegetables":
                self.feed+=1
                self.happy-=1
                self.drink-=1
                self.clean-=1
            if component == "dry food":
                self.feed+=2
                self.drink-=1
            if component=="fish":
                self.feed+=2
                self.drink-=1
                self.clean-=1
            if component=="honey":
                self.feed+=1
                self.clean-=1
                self.drink-=1
            if self.feed>10:
                self.feed=10
            if self.clean>10:
                self.clean=10
            if self.happy>10:
                self.happy=10
        if char == "drink":
            #"water", "milk", "vodka"
            if component == "water":
                self.drink+=3
            if component=="milk":
                self.drink+=2
                self.clean-=1
            if component == "vodka":
                self.drink-=1
                self.happy+=10
            if self.drink>10:
                self.drink=10
            if self.clean>10:
                self.clean=10
            if self.feed>10:
                self.feed=10
            if self.happy>10:
                self.happy=10
        if char == "happy":
            #"Walk", "Play with lazer", "Play with ball", "Hug"
            if component == "Walk":
                self.clean-=1
                self.happy+=3
                self.drink-=1
                self.feed-=1
            if component=="Play with lazer":
                self.happy+=2
                self.feed-=1
                self.drink-=1
            if component == "Play with ball":
                self.happy+=3
                self.feed-=1
                self.drink-=1
            if component=="Hug":
                self.happy+=2
            if self.happy>10:
                self.happy=10
            if self.clean>10:
                self.clean=10
            if self.feed>10:
                self.feed=10
            if self.drink>10:
                self.drink=10

class Cat(PET):
    def __init__(self, type, name, screen):
        super().__init__(type, name, screen)
    def increase(self, char, component):
        if char == "clean":
            if component == "bath":
                self.clean+=3
                self.happy-=2
            if component == "shower":
                self.clean+=2
                self.happy-=2
            if component == "bucket":
                self.clean+=1
                self.happy-=2
            if self.clean>10:
                self.clean=10
            if self.feed>10:
                self.feed=10
            if self.happy>10:
                self.happy=10
        if char == "feed":
            #"meet", "vegetables", "dry food", "fish", "honey"
            if component=="meet":
                self.feed+=3
                self.happy+=1
                self.drink-=1
            if component == "vegetables":
                self.feed+=1
                self.happy-=1
                self.drink-=1
            if component == "dry food":
                self.feed+=2
                self.drink-=1
                self.happy-=1
            if component=="fish":
                self.feed+=2
                self.drink-=1
                self.happy+=1
            if component=="honey":
                self.feed+=1
                self.happy+=1
                self.drink-=1
            if self.feed>10:
                self.feed=10
            if self.clean>10:
                self.clean=10
            if self.happy>10:
                self.happy=10
        if char == "drink":
            #"water", "milk", "vodka"
            if component == "water":
                self.drink+=3
            if component=="milk":
                self.drink+=2
                self.happy+=1
            if component == "vodka":
                self.drink-=1
                self.happy+=10
            if self.drink>10:
                self.drink=10
            if self.clean>10:
                self.clean=10
            if self.feed>10:
                self.feed=10
            if self.happy>10:
                self.happy=10
        if char == "happy":
            #"Walk", "Play with lazer", "Play with ball", "Hug"
            if component == "Walk":
                self.clean-=1
                self.happy+=1
                self.drink-=1
                self.feed-=1
            if component=="Play with lazer":
                self.happy+=3
                self.feed-=1
                self.drink-=1
            if component == "Play with ball":
                self.happy+=3
                self.feed-=1
                self.drink-=1
            if component=="Hug":
                self.happy+=1
            if self.happy>10:
                self.happy=10
            if self.clean>10:
                self.clean=10
            if self.feed>10:
                self.feed=10
            if self.drink>10:
                self.drink=10