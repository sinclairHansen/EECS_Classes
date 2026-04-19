# Name: Sinclair Hansen
# Student ID: 4413 6504
# Email: sihansen@umich.edu
# List who you have worked with on this homework:
# List any AI tool (e.g. ChatGPT, GitHub Copilot):
# Did your use of GenAI on this assignment align with your goals and guidelines in 
#    your Gen AI contract? If not, why?
# Used ChatGPT to help with general regex concepts and logic issues
# Yes because I used it to help with understanding of concepts,
# not directly doing coding itself

import re
import os
import unittest
from datetime import datetime
import tempfile


def read_user_records(file_name: str) -> list:
    """
    This function reads the file and returns a list of strings.
    Each string should contain all the information about one user.

    Args:
        file_name (str): The name of the file containing user data.

    Returns:
        user_info (list): A list of strings with each user's information.
    """
    list_out = []
    with open(file_name, 'r') as f:
        lines = f.read()
    if not lines:
        return list_out
    

    return re.split('\n\n', lines.strip())


def create_user_dict(user_info: list) -> dict:
    """
    This function takes a list of user information strings and returns a dictionary
    using usernames as keys and storing their birthday and age as of March 6, 2026.

    Args:
        user_info (list): A list of strings with each user's information.

    Returns:
        age_dict (dict): A dictionary with usernames as keys and a tuple of
                         (birthday, age) as values. Birthday is stored in MM/DD/YYYY.
    """
    age_dict = {}
    pattern = r'(\d{2})[/-](\d{2})[/-](\d{2,4})'
    pattern2 = r'@cc0uNT:(\w+)'
    today = datetime(2026, 3, 6)

    for user in user_info:
        birthday_match = re.search(pattern, user)
        user_match = re.search(pattern2, user)
        
        if not birthday_match or not user_match:
            continue
        month, day, year = birthday_match.groups()
        username = user_match.group(1)

        string_date = f"{month}/{day}/{year}"
        if len(year) == 2:
            if int(year) >= 26:
                year = '19' + year
            else:
                year = '20' + year
        date = datetime(int(year), int(month), int(day))

        age = today.year - date.year
        if (date.month, date.day) > (today.month, today.day):
            age -= 1

        age_dict[username] = (string_date, age)

    return age_dict


def summarize_password_strength(user_info: list) -> dict:
    """
    Summarizes password strength across all users by classifying passwords
    as weak, medium, or strong. Uses markers PASSWORD, P455W0RD, P4SSWORD (case-sensitive).
    Weak: at least 6 characters. Medium: at least 8, with lowercase and numbers.
    Strong: at least 10, with lowercase, uppercase, numbers, and special characters.

    Args:
        user_info (list): A list of strings with each user's information.

    Returns:
        password_strengths (dict): Keys 'weak', 'medium', 'strong'; values (count, passwords).
    """

    password_strengths = {}
    weak_list = []
    medium_list = []
    strong_list = []
    pattern = r'(?:PASSWORD|P455W0RD|P4SSWORD):\s*(.+)'
    for user in user_info:
        password_match = re.search(pattern, user)
        if not password_match:
            continue
        password = password_match.group(1).strip()
        int_count = 0
        lower_count = 0
        upper_count = 0
        special = 0
        for s in password:
            if s.isdigit():
                int_count += 1
            elif s.islower():
                lower_count += 1
            elif s.isupper():
                upper_count += 1
            else:
                special += 1
        if len(password) >= 10 and lower_count > 0 and upper_count > 0 and int_count > 0 and special > 0:
            strong_list.append(password)
        elif len(password) >= 8 and lower_count > 0 and int_count > 0:
            medium_list.append(password)

        elif len(password) >= 6:
            weak_list.append(password)
        else:
            weak_list.append(password)


    password_strengths['weak'] = (len(weak_list), weak_list)
    password_strengths['medium'] = (len(medium_list), medium_list)
    password_strengths['strong'] = (len(strong_list), strong_list)
    return password_strengths







def summarize_email_domains(user_info: list) -> dict:
    """
    Summarizes email domain usage across all users. For each user record, extracts
    username and all valid email addresses (local@domain.tld with at least one char
    in each part). Domains are case-insensitive. Returns a dict sorted by domain
    frequency (desc), then alphabetically by domain.

    Args:
        user_info (list): A list of strings with each user's full record.

    Returns:
        email_data (dict): Domain -> (count, sorted list of unique usernames).
    """
    email_pattern = r'\b[A-Za-z0-9._%+-]+@([A-Za-z0-9.-]+\.[A-Za-z]{2,})\b'
    account_pattern = r'@cc0uNT:(\w+)'

    domains = {}

    for user in user_info:
        email_match = re.findall(email_pattern, user)
        account_match = re.search(account_pattern, user)

        if not account_match:
            continue

        account = account_match.group(1)
        
        for email in email_match:
            email = email.lower()
            if email not in domains:
                in_list = [account]
                domains[email] = in_list
            else:
                in_list = domains[email]
                in_list.append(account)
                domains[email] = in_list
    sorted_domains = sorted(domains, key=lambda d: (-len(domains[d]), d))

    email_data = {}
    for domain in sorted_domains:
        sorted_usernames = sorted(domains[domain])
        email_data[domain] = (len(sorted_usernames), sorted_usernames)

    return email_data



################## EXTRA CREDIT ##################
def check_michigan_number(user_info: list) -> list:
    """
    This function checks for southeast Michigan phone numbers and returns a list of valid numbers.

    Args:
        user_info (list): A list of strings with each user's information.

    Returns:
        michigan_numbers (list): A list of valid southeast Michigan phone numbers.
    """
    pass


class TestAllFunc(unittest.TestCase):
    def setUp(self):
        # Set up a temporary directory
        self.test_dir = tempfile.TemporaryDirectory()

        # Paths for test files
        self.test_files = {
            "test1.txt": os.path.join(self.test_dir.name, "test1.txt"),
            "test2.txt": os.path.join(self.test_dir.name, "test2.txt"),
        }

        # Sample data to write to files
        sample_data = [
            "username: janeaccount\nPASSWORD: janeaccount123\n@cc0uNT:janeaccount\nBirthday: 06/28/2003\nEmail: jane@gmail.com\nPhone: 313-555-1234\n",
            "username: johnbanking\nP455W0RD: password\n@cc0uNT:johnbanking\nBirthday: 04-05-2004\nEmail: john@bank.net\nPhone: 734-987-1234\n",
            "",
            "username: emthompson\nP455W0RD: Thompson!321\n@cc0uNT:emthompson\nBirthday: 05/11/2002\nEmail: em@google.com\nPhone: 313-123-4567\n"
        ]

        # Write data to test files
        with open(self.test_files["test1.txt"], 'w') as f:
            f.write(sample_data[0] + '\n\n' + sample_data[1])
        with open(self.test_files["test2.txt"], 'w') as f:
            f.write('\n\n'.join(sample_data))

    def tearDown(self):
        self.test_dir.cleanup()

    def test_read_user_records(self):
        # 2 asserts total, one per file
        # TODO: implement this test case
        user_list = read_user_records(self.test_files['test1.txt'])
        user_list2 = read_user_records(self.test_files['test2.txt'])
        self.assertEqual(len(user_list), 2)
        self.assertEqual(len(user_list2), 4)

        self.assertEqual(user_list[0], "username: janeaccount\nPASSWORD: janeaccount123\n@cc0uNT:janeaccount\nBirthday: 06/28/2003\nEmail: jane@gmail.com\nPhone: 313-555-1234")

    def test_create_user_dict(self):
        # 2 asserts total, one per file
        # TODO: implement this test case
        l1 = read_user_records(self.test_files['test1.txt'])
        l2 = read_user_records(self.test_files['test2.txt'])
        d1 = create_user_dict(l1)
        d2 = create_user_dict(l2)

        self.assertEqual(d1['janeaccount'], ('06/28/2003', 22))
        self.assertEqual(d1['johnbanking'], ('04/05/2004', 21))
        self.assertEqual(d2['emthompson'], ("05/11/2002", 23))


    def test_summarize_password_strength(self):
        # 2 asserts total, one per file
        # TODO: implement this test case
        l1 = read_user_records(self.test_files["test1.txt"])
        d1 = summarize_password_strength(l1)

        l2 = read_user_records(self.test_files["test2.txt"])
        d2 = summarize_password_strength(l2)

        self.assertEqual(d1['weak'][0], 1)
        self.assertEqual(d1["medium"][0], 1)
        self.assertEqual(d2["strong"][0], 1)
        self.assertEqual(d2["medium"][0], 1)

    def test_summarize_email_domains(self):
        # 2 asserts total, one per file
        # TODO: implement this test case
        l1 = read_user_records(self.test_files["test1.txt"])
        d1 = summarize_email_domains(l1)

        l2 = read_user_records(self.test_files["test2.txt"])
        d2 = summarize_email_domains(l2)


        self.assertEqual(d1["gmail.com"], (1, ["janeaccount"]))
        self.assertEqual(d2["google.com"], (1, ["emthompson"]))

    def test_check_michigan_number(self):
        # 2 asserts total, one per file
        # TODO: implement this test case
        pass

def main():
    unittest.main(verbosity=2)


if __name__ == "__main__":
    main()
