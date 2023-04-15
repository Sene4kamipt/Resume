import time

import telebot
import requests
import bs4

token = "5302529907:AAEryrJ3agjYfJw_-9uvM4TW92-gUpSooLQ"
bot = telebot.TeleBot(token)
global correct_answer
global score
score =0
global flag
flag =1

@bot.message_handler(commands=['start'])
def start_message(message):
  bot.send_message(message.chat.id,"Привет! \n Choose a pack you want to play")
  markup = telebot.types.ReplyKeyboardMarkup(resize_keyboard=True, one_time_keyboard=True)
  btn1 = telebot.types.KeyboardButton("XII Кубок Европы по интеллектуальным играм среди студентов (Витебск). Эрудит-квартет")
  btn2 = telebot.types.KeyboardButton("XII Кубок Европы по интеллектуальным играм среди студентов (Витебск). Своя игра")
  markup.add(btn1, btn2)
  bot.send_message(message.chat.id, "XII Кубок Европы по интеллектуальным играм среди студентов (Витебск). Эрудит-квартет \n XII Кубок Европы по интеллектуальным играм среди студентов (Витебск). Своя игра", reply_markup=markup)

@bot.message_handler(func = lambda message: message.text == "XII Кубок Европы по интеллектуальным играм среди студентов (Витебск). Эрудит-квартет")
def check_answer(message):
  global correct_answer
  global score
  global flag
  score =0
  resp = requests.get("https://db.chgk.info/tour/eu16stek").text
  soup = bs4.BeautifulSoup(resp, 'lxml')
  r = soup.h2
  bot.send_message(message.chat.id, r.text)
  for theme in soup.find_all('div', style="margin-top:20px;"):
    bot.send_message(message.chat.id, theme.strong.text)
    counter = 0
    i = 0
    while counter != 1:
      if theme.text[i] == ":":
        counter += 1
      i += 1
    s = ""
    while theme.text[i] != ".":
      s += theme.text[i]
      i += 1
    bot.send_message(message.chat.id, s + ".")
    counter = 1
    flag = 0
    for i in theme.find_all('p'):
      if counter:
        bot.send_message(message.chat.id, i.text)
        counter = 0
        flag += 1
      else:
        correct_answer = i.text
        correct_answer = correct_answer[6:]
        ans = ""
        for j in range(len(correct_answer) - 1, -1, -1):
          if correct_answer[j] == "[" or correct_answer[j] == "{" or correct_answer[j] == "(":
            ans = ""
          else:
            ans = correct_answer[j] + ans
        correct_answer = ans
        counter = 1
        print(correct_answer)
        time.sleep(10)
        bot.send_message(message.chat.id, i.text)
    bot.send_message(message.chat.id, "Your score is: " + score)



@bot.message_handler(func = lambda message: message.text == "XII Кубок Европы по интеллектуальным играм среди студентов (Витебск). Своя игра")
def check_answer(message):
  global correct_answer
  global score
  global flag
  score = 0
  resp = requests.get("https://db.chgk.info/tour/eu16stsv").text
  soup = bs4.BeautifulSoup(resp, 'lxml')
  r = soup.h2
  bot.send_message(message.chat.id, r.text)
  for theme in soup.find_all('div', style="margin-top:20px;"):
    bot.send_message(message.chat.id, theme.strong.text)
    counter = 0
    i = 0
    while counter != 1:
      if theme.text[i] == ":":
        counter += 1
      i += 1
    s = ""
    while theme.text[i] != ".":
      s += theme.text[i]
      i += 1
    bot.send_message(message.chat.id, s + ".")
    counter = 1
    flag = 0
    for i in theme.find_all('p'):
      if counter:
        bot.send_message(message.chat.id, i.text)
        counter = 0
        flag += 1
      else:
        correct_answer = i.text
        correct_answer = correct_answer[6:]
        ans=""
        for j in range (len(correct_answer)-1, -1, -1):
          if correct_answer[j]=="[" or correct_answer[j]=="{" or correct_answer[j] == "(":
            ans=""
          else:
            ans = correct_answer[j]+ans
        correct_answer=ans
        counter = 1
        print(correct_answer)
        time.sleep(10)
        bot.send_message(message.chat.id, i.text)
    bot.send_message(message.chat.id, "Your score is: "+ score)


@bot.message_handler(content_types= 'text')
def handle_text(message):
  global score
  global flag
  if correct_answer == message.text:
    bot.send_message(message.chat.id, "right")
    score+=10*flag
  else:
    bot.send_message(message.chat.id, "wrong")
    score-=10*flag

bot.polling()