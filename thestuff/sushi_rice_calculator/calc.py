# https://makemysushi.com/Recipes/how-to-make-sushi-rice

import math

while True:
  try:
    number = int(input("How many sushi rolls are you making? "))
    break
  except ValueError:
    print("Invalid input. Please enter an integer value.")

rice = number / 3
value_rice = round(rice, 3)
value_water = (math.floor(10 * rice * 1.2 * 2) / 20)
value_vinegar = round((10 * rice * 16 / 6) / 10, 1)
value_sugar = round((10 * rice * 2 / 3) / 10, 1)
value_salt = round((10 * rice * 2 / 3) / 10, 1)

# Metric Conversions: https://coolconversion.com/cooking-volume-weight/density-database-FAO.pdf
print(f"""
    Rice:
        Rice:    {value_rice * 200} g \t {value_rice} Cups
        Water:   {value_water * 237} g \t {value_water} Cups

    Seasoning: (mix in small pot on medium heat until solids are dissolved)
        Vinegar: {value_vinegar * 14.4} g \t {value_vinegar} Tablespoons
        Sugar:   {value_sugar * 12.5} g \t {value_sugar} Tablespoons
        Salt:    {value_salt * 4.16} g \t {value_salt} Teaspoons
""")



