# Name: Matthew Huang and Sinclair Hansen
# Student ID: 17382251, 44136504
# Email: matthhua@umich.edu, sihansen@umich.edu
# Who or what you worked with on this homework (including generative AI like ChatGPT):
# If you worked with generative AI also add a statement for how you used it.
# e.g.:
# Asked ChatGPT hints for debugging and suggesting the general structure of the code
# Did your use of GenAI on this assignment align with your goals and guidelines in 
#    your Gen AI contract? If not, why?
# Matthew: I did not use GenAI on this assignment.
# Sinclair: I did not use GenAI on this assignment.

import csv
import os
import unittest
from matthew_calculation_functions import *
from sinclair_functions import *

def read_input(input_file):

    # Read in lines from file and create data dictionary.
    data_dict = {}
    dir = os.path.dirname(__file__)
    with open(os.path.join(dir, input_file)) as csv_input:
        csv_reader = csv.reader(csv_input)

        # Get list of headers to use as inner dictionary keys.
        headers = next(csv_reader)

        # Create and insert dictionaries into data_dict.
        row = 1
        for line in csv_reader:
            inner_dict = {}
            for i in range(1, len(headers)):
                inner_dict[headers[i]] = line[i]
            
            # Add to data_dict.
            data_dict[row] = inner_dict
            row += 1

        # Return the resulting dictionary without header.
        return data_dict
    

def write_output(dict_list):
    """Prints the info in dict_list which is a list of nested dictionaries."""

    # Open output file to write to.
    with open("results.txt", "w") as outputFile:

        # Loop through each nested dictionary.
        for dict in dict_list:
            title = dict.get("Title", None)
            outputFile.write("Title: " + str(title) + "\n")
            for outer_key in sorted(dict):
                if outer_key != "Title":
                    outputFile.write(outer_key + ":\n")
                    inner_dict = dict[outer_key]
                    for info, val in inner_dict.items():   
                        outputFile.write(" " + str(info) + ": " + str(val) + "\n")

            outputFile.write("\n")



def main():
    dict_list = []
    data_dict = read_input("test_subset_penguins.csv")
    dict_list.append(avg_bill_length_diff_mvf(data_dict))
    dict_list.append(abv_avg_mass_percent(data_dict))
    dict_list.append(avg_flip_len_male(data_dict))
    dict_list.append(med_gend_mass(data_dict))
    write_output(dict_list)


# Test cases
class Tests(unittest.TestCase):
    def setUp(self):
        self.data_dict = read_input("test_subset_penguins.csv")

    def test_abv_avg_mass_percent(self):
        islands_dict = abv_avg_mass_percent(self.data_dict)

        # Look at values in return dictionary:
        # 08_num_penguins
        # 08_mass_total
        # 09_num_penguins
        # 09_mass_total
        # 08_avg_mass
        # 09_avg_mass
        # 08_abv_avg_mass_count
        # 09_abv_avg_mass_count
        # percent_diff

        # Test to see that rows with NA are not considered.
        # The Biscoe island has a row with NAs in the subset.
        self.assertTrue("Biscoe" in islands_dict)
        biscoe_dict = islands_dict.get("Biscoe")
        self.assertEqual(biscoe_dict["08_num_penguins"], 4)
        self.assertEqual(biscoe_dict["09_num_penguins"], 2)
        self.assertEqual(biscoe_dict["08_abv_avg_mass_count"], 1)
        self.assertEqual(biscoe_dict["09_abv_avg_mass_count"], 1)

        # Comparing floats so use AlmostEqual
        self.assertAlmostEqual(biscoe_dict["08_mass_total"], 17600, 3)
        self.assertAlmostEqual(biscoe_dict["09_mass_total"], 10400, 3)
        self.assertAlmostEqual(biscoe_dict["08_avg_mass"], 4400, 3)
        self.assertAlmostEqual(biscoe_dict["09_avg_mass"], 5200, 3)
        self.assertAlmostEqual(biscoe_dict["percent_diff"], 25.0, 3)

        # Test for usual case.
        # Dream was chosen because Torgersen has no data from 2008 to 2009.
        self.assertTrue("Dream" in islands_dict)
        dream_dict = islands_dict.get("Dream")

        self.assertEqual(dream_dict["08_num_penguins"], 3)
        self.assertEqual(dream_dict["09_num_penguins"], 4)
        self.assertEqual(dream_dict["08_abv_avg_mass_count"], 1)
        self.assertEqual(dream_dict["09_abv_avg_mass_count"], 2)

        # Comparing floats so use AlmostEqual
        self.assertAlmostEqual(dream_dict["08_mass_total"], 11550, 3)
        self.assertAlmostEqual(dream_dict["09_mass_total"], 14050, 3)
        self.assertAlmostEqual(dream_dict["08_avg_mass"], 3850, 3)
        self.assertAlmostEqual(dream_dict["09_avg_mass"], 3512.5, 3)
        self.assertAlmostEqual(dream_dict["percent_diff"], 16.667, 3)

    def test_avg_bill_length_diff_mvf(self):
        species_dicts = avg_bill_length_diff_mvf(self.data_dict)

        # Check the following data:
        # num_male
        # num_female
        # bill_total_m
        # bill_total_f
        # male_avg
        # female_avg
        # avg_diff

        # Test to see that rows with NA are not included.
        # The Gentoo species has two rows where the sex is NA.
        self.assertTrue("Gentoo" in species_dicts)
        gentoo_dict = species_dicts.get("Gentoo")
        self.assertEqual(gentoo_dict["num_male"], 3)
        self.assertEqual(gentoo_dict["num_female"], 3)

        # Comparing floats so use almostEqual.
        self.assertAlmostEqual(gentoo_dict["bill_total_m"], 151.1, 3)
        self.assertAlmostEqual(gentoo_dict["bill_total_f"], 144.3, 3)
        self.assertAlmostEqual(gentoo_dict["male_avg"], 50.367, 3)
        self.assertAlmostEqual(gentoo_dict["female_avg"], 48.1, 3)
        self.assertAlmostEqual(gentoo_dict["avg_diff"], 2.267, 3)

        # Usual test case with Chinstrap species.
        self.assertTrue("Chinstrap" in species_dicts)
        chinstrap_dict = species_dicts.get("Chinstrap")
        self.assertEqual(chinstrap_dict["num_male"], 4)
        self.assertEqual(chinstrap_dict["num_female"], 3)

        # Comparing floats so use almostEqual.
        self.assertAlmostEqual(chinstrap_dict["bill_total_m"], 201.3, 3)
        self.assertAlmostEqual(chinstrap_dict["bill_total_f"], 135.1, 3)
        self.assertAlmostEqual(chinstrap_dict["male_avg"], 50.325, 3)
        self.assertAlmostEqual(chinstrap_dict["female_avg"], 45.033, 3)
        self.assertAlmostEqual(chinstrap_dict["avg_diff"], 5.292, 3)



    def test_avg_flip_len_male(self):
        species_dicts = avg_flip_len_male(self.data_dict)

        # Test to see that rows with NA are not included and only males are used.
        self.assertTrue("Gentoo" in species_dicts)
        gentoo_dict = species_dicts.get("Gentoo")
        self.assertTrue(isinstance(gentoo_dict, dict))

        # Find a year that actually exists for male Gentoo with non-NA flipper length
        years = []
        for p in self.data_dict.values():
            if (p.get("species") == "Gentoo"
                and p.get("sex") == "male"
                and p.get("year") != "NA"
                and p.get("flipper_length_mm") != "NA"):
                years.append(p.get("year"))

        self.assertTrue(len(years) > 0)
        target_year = years[0]

        if target_year.isdigit() and int(target_year) in gentoo_dict:
            year_key = int(target_year)
        else:
            year_key = target_year

        self.assertTrue(year_key in gentoo_dict)

        # Compute expected mean for that species/year using the raw data_dict
        flips = []
        for p in self.data_dict.values():
            if (p.get("species") == "Gentoo"
                and p.get("sex") == "male"
                and p.get("year") != "NA"
                and p.get("flipper_length_mm") != "NA"):
                if str(p.get("year")) == str(target_year):
                    flips.append(float(p.get("flipper_length_mm")))

        expected_mean = statistics.mean(flips) if len(flips) > 0 else 0

        # Comparing floats so use AlmostEqual
        self.assertAlmostEqual(gentoo_dict[year_key], expected_mean, 3)



    def test_med_gend_mass(self):

        # Checks if the genders are both accounted for
        # Calculates median and compared to each category in the output dict
        islands_dict = med_gend_mass(self.data_dict)

        # Check that expected islands exist
        self.assertTrue("Torgersen" in islands_dict)
        self.assertTrue("Biscoe" in islands_dict)
        self.assertTrue("Dream" in islands_dict)

        torg_dict = islands_dict.get("Torgersen")
        bisc_dict = islands_dict.get("Biscoe")
        dream_dict = islands_dict.get("Dream")

        # Check keys exist
        self.assertTrue("male" in torg_dict and "female" in torg_dict)
        self.assertTrue("male" in bisc_dict and "female" in bisc_dict)
        self.assertTrue("male" in dream_dict and "female" in dream_dict)

    # Compute expected medians directly from the raw data (exclude NA)
        def expected_median(island, sex):
            masses = []
            for p in self.data_dict.values():
                if (p.get("island") == island
                    and p.get("sex") == sex
                    and p.get("body_mass_g") != "NA"
                    and p.get("island") != "NA"
                    and p.get("sex") != "NA"):
                    masses.append(float(p.get("body_mass_g")))
            return statistics.median(masses) if len(masses) > 0 else 0

        # Comparing floats so use AlmostEqual
        self.assertAlmostEqual(torg_dict["male"], expected_median("Torgersen", "male"), 3)
        self.assertAlmostEqual(torg_dict["female"], expected_median("Torgersen", "female"), 3)

        self.assertAlmostEqual(bisc_dict["male"], expected_median("Biscoe", "male"), 3)
        self.assertAlmostEqual(bisc_dict["female"], expected_median("Biscoe", "female"), 3)

        self.assertAlmostEqual(dream_dict["male"], expected_median("Dream", "male"), 3)
        self.assertAlmostEqual(dream_dict["female"], expected_median("Dream", "female"), 3)


if __name__=="__main__":
    main()
    unittest.main()