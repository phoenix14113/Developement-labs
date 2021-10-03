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
        self.driver.find_element_by_xpath(
            "//button[@id='mask-search-button']/i").click()
        self.driver.implicitly_wait(5)  # seconds
        xpath = "//search-results[contains(@ng-reflect-query,'" + name + "')]"
        self.driver.find_element_by_xpath(xpath)
        xpath = "//h4[contains(text(),'" + name + "')]"
        result = self.driver.find_elements_by_xpath(xpath)
        return result
# add login(), updateProfile(), and close() to ASWWU
# iterate over a dictionary with `for key, value in dict.items():`

    def login(self, username, password):
        xpath = "//a[contains(@href, 'https://saml.aswwu.com/?sso&redirect=/mask/search')]"
        self.driver.find_element_by_xpath(xpath).click()
        self.driver.find_element_by_id('userNameInput').clear()
        self.driver.find_element_by_id('userNameInput').send_keys(sys.argv[1])
        self.driver.find_element_by_id('passwordInput').clear()
        self.driver.find_element_by_id(
            'passwordInput').send_keys(sys.argv[2], Keys.ENTER)

    def updateProfile(self, dict):
        self.driver.find_element_by_id('bubbleicon').click()
        self.driver.find_element_by_xpath(
            "//a[contains(@href, 'https://aswwu.com/mask/update')]").click()
        for key, value in dict.items():
            self.driver.find_element_by_id(key).clear()
            self.driver.find_element_by_id(key).send_keys(value)
        self.driver.find_element_by_id("submit").click()

    def close(self):
        self.driver.close()


def main():
    aswwu = ASWWU()
    assert(len(aswwu.searchMask('Taylor')) == 11)

    # provide the user email and password as command-line arguments (for security)
    aswwu.login(sys.argv[1], sys.argv[2])
    aswwu.updateProfile({
        'favorite_booksinput': 'F.A. Hayek, The Road to Serfdom',
        'quoteinput': 'The road to hell is paved with good intentions.'})
    aswwu.close()


if __name__ == "__main__":
    main()
