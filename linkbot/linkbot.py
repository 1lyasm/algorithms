from selenium import webdriver
from selenium.webdriver.common.by import By

class Page:
    def __init__(self, driver):
        self.driver = driver

class SignInPage(Page):
    def login(self):
        uname_box = self.driver.find_element(By.ID, 'session_key')
        passw_box = self.driver.find_element(By.ID, 'session_password')
        sign_button = self.driver.find_element(
            By.CLASS_NAME, 'sign-in-form__submit-button')
        uname_box.click()
        uname_box.send_keys("il.mystafa@gmail.com")
        passw_box.click()
        passw_box.send_keys("Ilyas-2004")
        sign_button.click()
        return


class HomePage(Page):
    def open_jobs_pg(self):
        job_pg_icon = self.driver.find_element(
            By.CLASS_NAME, 'global-nav__primary-item')
        job_pg_icon.click()
        return

class JobsPage(Page):

    def open_jobs(self):
        self.driver.get("https://www.linkedin.com/jobs/")
        SignInPage(self.driver).login()
        return

    def open_job_alerts(self):
        self.driver.get("https://www.linkedin.com/jobs/jam/")
        job_alert_lnk = self.driver.find_element(
            By.PARTIAL_LINK_TEXT,
            "Jobs in Worldwide")
        job_alert_lnk.click()
        return


def main():
    driver = webdriver.Chrome()
    jobs_pg = JobsPage(driver)
    jobs_pg.open_jobs()
    jobs_pg.open_job_alerts()

    while True:
        pass

if __name__ == "__main__":
    main()