import time
import requests
import sys
from selenium import webdriver
from selenium.webdriver.common.keys import Keys



def main():
  names = [ "Benko", "DePaula", "Fairchild", "Hartman", "Herbel", 
           "Hernandez", "Jones", "Moody", "Price", "Reklai", "Riggs", 
           "Smith", "Sukachevin", "Taylor", "Thomsen", "Tinker" ]
  start = time.time()
  for name in names:
    r = requests.get("https://aswwu.com/server/search/1920/" + name)
    print(name.encode() in r.content, r.status_code)
  end = time.time()
  print(end - start)


if __name__ == "__main__":
    main()
