import sys
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
driver = webdriver.Firefox()
driver.implicitly_wait(5)  # seconds
driver.get('https://aswwu.com/')

# search mask
driver.find_element_by_xpath(
    "//a[contains(@href, 'https://aswwu.com/mask')]").click()
driver.find_element_by_id('mask-search-query').clear()
driver.find_element_by_id('mask-search-query').send_keys('adam')
driver.find_element_by_xpath("//button[@id='mask-search-button']/i").click()
driver.find_element_by_xpath(
    "//search-results[contains(@ng-reflect-query,'adam')]")
Adam = driver.find_elements_by_xpath("//h4[contains(text(),'Adam')]")
assert(len(Adam) == 8)

# login
driver.find_element_by_xpath(
    "//a[contains(@href, 'https://saml.aswwu.com/?sso&redirect=/mask/search')]").click()
driver.find_element_by_id('userNameInput').clear()
driver.find_element_by_id('userNameInput').send_keys(sys.argv[1])
driver.find_element_by_id('passwordInput').clear()
driver.find_element_by_id('passwordInput').send_keys(sys.argv[2], Keys.ENTER)

# update profile
driver.find_element_by_id('bubbleicon').click()
driver.find_element_by_xpath(
    "//a[contains(@href, 'https://aswwu.com/mask/update')]").click()
driver.find_element_by_id('hobbiesinput').clear()
driver.find_element_by_id('hobbiesinput').send_keys("programming")
driver.find_element_by_id('favorite_foodinput').clear()
driver.find_element_by_id('favorite_foodinput').send_keys("pizza")
driver.find_element_by_id("submit").click()

# close window
driver.close()
