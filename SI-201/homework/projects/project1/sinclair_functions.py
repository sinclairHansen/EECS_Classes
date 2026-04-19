

import statistics


# Median body mass of male and female penguins across each island.
# Columns Used: body_mass, sex, island
def med_gend_mass(df):
    male_list = []
    female_list = []
    torg_list_female = [] # Torgersen
    bisc_list_female = [] # Biscoe
    dream_list_female = [] # Dream
    torg_list_male = [] # Torgersen
    bisc_list_male = [] # Biscoe
    dream_list_male = [] # Dream
    for penguin in df.values():

        if(penguin['sex'] != "NA" and penguin['body_mass_g'] != "NA"
           and penguin['island'] != "NA" and penguin['year'] != "NA"):
            if penguin['sex'] == 'male':
                male_list.append(penguin)
            else:
                female_list.append(penguin)

    # Sorting penguins into lists based on gender
    for penguin in male_list:
        if penguin['island'] == "Torgersen":
            torg_list_male.append(float(penguin['body_mass_g']))
        elif penguin['island'] == "Dream":
            dream_list_male.append(float(penguin['body_mass_g']))
        elif penguin['island'] == "Biscoe":
            bisc_list_male.append(float(penguin['body_mass_g']))


    for penguin in female_list:
        if penguin['island'] == "Torgersen":
            torg_list_female.append(float(penguin['body_mass_g']))
        elif penguin['island'] == "Dream":
            dream_list_female.append(float(penguin['body_mass_g']))
        elif penguin['island'] == "Biscoe":
            bisc_list_female.append(float(penguin['body_mass_g']))

        
    # Calc med and put stats in for each island
    torg_dic = {}
    torg_dic['male'] = statistics.median(torg_list_male) if len(torg_list_male) > 0 else 0
    torg_dic['female'] = statistics.median(torg_list_female) if len(torg_list_female) > 0 else 0

    bisc_dict = {}
    bisc_dict['male'] = statistics.median(bisc_list_male) if len(bisc_list_male) > 0 else 0
    bisc_dict['female'] = statistics.median(bisc_list_female) if len(bisc_list_female) > 0 else 0

    dream_dict = {}
    dream_dict['male'] = statistics.median(dream_list_male) if len(dream_list_male) > 0 else 0
    dream_dict['female'] = statistics.median(dream_list_female) if len(dream_list_female) > 0 else 0

    d_out = {}
    d_out['Torgersen'] = torg_dic
    d_out['Biscoe'] = bisc_dict
    d_out['Dream'] = dream_dict

    d_out['Title'] = "Median body mass of male and female penguins across each island."

    return d_out
        


# Calculate the average flipper length of male penguins of each species across every year.
# Columns Used: Flipper length, sex, species, year
def avg_flip_len_male(data_dict):
    # collect: species -> year -> list of flipper lengths
    buckets = {}

    for p in data_dict.values():
        sex = p.get("sex")
        species = p.get("species")
        year = p.get("year")
        flip = p.get("flipper_length_mm")

        if sex != "male":
            continue
        if species ==  "NA" or year =="NA" or flip =="NA":
            continue

        year = int(year)
        flip = float(flip)

        buckets.setdefault(species, {}).setdefault(year, []).append(flip)

    # compute means
    d_out = {}
    for species, years in buckets.items():
        d_out[species] = {}
        for year, flips in years.items():
            d_out[species][year] = (sum(flips) / len(flips)) if len(flips) > 0 else 0

    d_out['Title'] = "Calculate the average flipper length of male penguins of each species across every year."
    return d_out

