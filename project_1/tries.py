import pygame
from pygame.locals import *
import time
from BUTTON import Button
from BUTTON import Show_Button
from BUTTON import Do_Button
from PET import PET, Dog, Cat
from BUTTON import Show_Buttons_Button
 
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GRAY = (200, 200, 200)

pygame.init()
screen = pygame.display.set_mode((1000, 500))
pygame.display.set_caption("YOUR TAMAGOCHI")

pet_type_input = ''
font_for_pet_type = pygame.font.SysFont('arial', 48)
pet_type_input_img = font_for_pet_type.render(pet_type_input, True, BLACK)
font_for_ask_pet_type=pygame.font.SysFont('arial',24)
text_with_pet_type_quest = font_for_ask_pet_type.render("Enter your pet's type:", True, BLACK)

rect = pet_type_input_img.get_rect()
rect.topleft = (20, 60)
cursor = Rect(rect.topright, (3, rect.height))

pet_name_input = ''
font_for_pet_name = pygame.font.SysFont('arial', 48)
pet_name_input_img = font_for_pet_type.render(pet_type_input, True, BLACK)
font_for_ask_pet_name=pygame.font.SysFont('arial',24)
text_with_pet_name_quest = font_for_ask_pet_type.render("How will we call it", True, BLACK)

text_with_end = font_for_pet_type.render("YOUR PET IS DEAD", True, RED)
dead = False
text_with_warning_drink = font_for_ask_pet_type.render("Your pet wants to drink", True, RED)
text_with_warning_clean = font_for_ask_pet_type.render("Your pet wants shower", True, RED)
text_with_warning_feed = font_for_ask_pet_type.render("Your pet wants to eat", True, RED)
text_with_warning_happy = font_for_ask_pet_type.render("Your pet wants to play", True, RED)

rect2 = pet_name_input_img.get_rect()
rect2.topleft = (20, 60)
cursor2 = Rect(rect2.topright, (3, rect2.height))

pet= PET("DOG", "SENYA", screen)

running = True
background = GRAY
input_of_pet_type=True
input_of_pet_name=False

button1 = Show_Button(
    "Which types are avaliable?",
    (400, 20),
    font=30,
    lines = ("CAT", "DOG"),
    pos_lines=(400,50),
    bg = "white",
    feedback = "Close avaliable types")

button_clean = Show_Buttons_Button(
    "Wash",
    (400, 450),
    font=30,
    lines = ["bath", "shower", "bucket"],
    pos_lines=(750,150),
    char = "clean",
    screen =screen,
    bg = "white",
    feedback = "Close")

button_feed = Show_Buttons_Button(
    "Feed",
    (300, 450),
    font=30,
    lines = ["meet", "vegetables", "dry food", "fish", "honey"],
    pos_lines= (750,150),
    char = "feed",
    screen =screen,
    bg = "white",
    feedback = "Close")

button_drink = Show_Buttons_Button(
    "Water",
    (200, 450),
    font=30,
    lines = ["water", "milk", "vodka"],
    pos_lines= (750,150),
    char = "drink",
    screen =screen,
    bg = "white",
    feedback = "Close")

button_happy = Show_Buttons_Button(
    "Make Happy",
    (500, 450),
    font=30,
    lines = ["Walk", "Play with lazer", "Play with ball", "Hug"],
    pos_lines= (750,150),
    char = "happy",
    screen =screen,
    bg = "white",
    feedback = "Close")

while running:
    for event in pygame.event.get():
        if input_of_pet_name:
            if event.type == KEYDOWN:
                if event.key == K_BACKSPACE:
                    if len(pet_name_input)>0:
                        pet_name_input = pet_name_input[:-1]
                elif event.key == K_RETURN:
                    input_of_pet_name=False
                    if pet_type_input=="DOG":
                        pet = Dog(pet_type_input, pet_name_input, screen)
                    if pet_type_input == "CAT":
                        pet= Cat(pet_type_input, pet_name_input, screen)
                    print(1)
                else:    
                    pet_name_input += event.unicode
                pet_name_input_img = font_for_pet_name.render(pet_name_input, True, BLACK)
                rect2.size=pet_name_input_img.get_size()
                cursor2.topleft = rect2.topright
        if event.type == QUIT:
            running = False  
        if input_of_pet_type:
            if event.type == KEYDOWN:
                if event.key == K_BACKSPACE:
                    if len(pet_type_input)>0:
                        pet_type_input = pet_type_input[:-1]
                elif event.key == K_RETURN:
                    input_of_pet_type=False
                    input_of_pet_name=True
                    print(1)
                else:    
                    pet_type_input += event.unicode
                pet_type_input_img = font_for_pet_type.render(pet_type_input, True, BLACK)
                rect.size=pet_type_input_img.get_size()
                cursor.topleft = rect.topright
            button1.click(event, screen)
        if not input_of_pet_name and not input_of_pet_type:
            button_clean.click(event, pet)
            button_feed.click(event,pet)
            button_drink.click(event,pet)
            button_happy.click(event, pet)
            for i in range (len(button_clean.arr)):
                button_clean.arr[i].click(event,pet)
            for i in range (len(button_happy.arr)):
                button_happy.arr[i].click(event,pet)
            for i in range (len(button_drink.arr)):
                button_drink.arr[i].click(event,pet)
            for i in range (len(button_feed.arr)):
                button_feed.arr[i].click(event,pet)
        
    screen.fill(background)
    if input_of_pet_type:
        screen.blit(pet_type_input_img, rect)
        button1.show(screen)
        screen.blit(text_with_pet_type_quest, (20, 20))
        if time.time() % 1 > 0.5:
            pygame.draw.rect(screen, BLACK, cursor)
    if input_of_pet_name:
        screen.blit(pet_name_input_img, rect)
        screen.blit(text_with_pet_name_quest, (20, 20))
        if time.time() % 1 > 0.5:
            pygame.draw.rect(screen, BLACK, cursor2)
    if not input_of_pet_name and not input_of_pet_type and not dead:
        pet.draw()
        button_clean.show(screen)
        button_feed.show(screen)
        button_drink.show(screen)
        button_happy.show(screen)
        if time.time()-pet.time_create_clean()>20:
            pet.clean-=1
            pet.time_create_clean_plus()
        if pet.clean==0:
            dead = True
        if pet.clean<=2:
            screen.blit(text_with_warning_clean,(750,30))
        if time.time()-pet.time_create_feed()>10:
            pet.feed-=1
            pet.time_create_feed_plus()
        if pet.feed==0:
            dead = True
        if pet.feed<=2:
            screen.blit(text_with_warning_feed,(750,90))
        if time.time()-pet.time_create_drink()>5:
            pet.drink-=1
            pet.time_create_drink_plus()
        if pet.drink==0:
            dead = True
        if pet.drink<=2:
            screen.blit(text_with_warning_drink,(750,60))
        if time.time()-pet.time_create_happy()>30:
            pet.happy-=1
            pet.time_create_happy_plus()
        if pet.happy==0:
            dead = True
        if pet.happy<=2:
            screen.blit(text_with_warning_happy,(750,120))
    if dead:
        screen.blit(text_with_end, (49,49))
    pygame.display.update()

pygame.quit()