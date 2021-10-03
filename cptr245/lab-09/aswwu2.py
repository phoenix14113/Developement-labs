import time
import sys
from selenium import webdriver
from selenium.webdriver.common.keys import Keys


class ASWWU:
    def __init__(self):
        self.driver = webdriver.Firefox()
        self.driver.implicitly_wait(5)  # seconds
        self.driver.get('https://aswwu.com/')

    def searchMask(self, name):
        xpath = "//a[contains(@href, 'https://aswwu.com/mask')]"
        self.driver.find_element_by_xpath(xpath).click()
        self.driver.find_element_by_id(
            'mask-search-query').send_keys(name)
        # weird bug. if this function is called twice the second time the clicking on the search icon won't work
        time.sleep(1.0)
        self.driver.find_element_by_xpath(
            "//button[@id='mask-search-button']/i").click()
        time.sleep(1.0)
        self.driver.implicitly_wait(5)  # seconds
        xpath = "//search-results[contains(@ng-reflect-query,'" + name + "')]"
        self.driver.find_element_by_xpath(xpath)
        xpath = "//h4[contains(text(),'" + name + "')]"
        result = self.driver.find_elements_by_xpath(xpath)
        return result
# add login(), updateProfile(), and close() to ASWWU
# iterate over a dictionary with `for key, value in dict.items():`

    
    def close(self):
        self.driver.close()


def main():
  names = [ "Benko", "DePaula", "Fairchild", "Hartman", "Herbel", 
           "Hernandez", "Jones", "Moody", "Price", "Reklai", "Riggs", 
           "Smith", "Sukachevin", "Taylor", "Thomsen", "Tinker" ]
  start = time.time()
  aswwu = ASWWU()
  for name in names:
    aswwu.searchMask(name)
  aswwu.close()
  end = time.time()
  print(end - start)


if __name__ == "__main__":
    main()
