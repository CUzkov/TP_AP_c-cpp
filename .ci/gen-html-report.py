import lxml
from bs4 import BeautifulSoup

with open("index.html", "r") as f:
    
    contents = f.read()
    soup = BeautifulSoup(contents, "lxml")

    file_names = soup.find_all("td", class_="coverFile")

    numbers = soup.find_all("td", class_=(
        "coverPerHi", 
        "coverNumHi",
        "coverPerLo",
        "coverNumLo",
        "coverPerMed", 
        "coverNumMed",
        ))

    suop_new = BeautifulSoup("<div></div>")

    name_dict = (
        "Line Coverage",
        "Line Coverage",
        "Functions",
        "Functions",
    )

    counter = 0

    for file_name in file_names:
        part = BeautifulSoup("<div>{}</div>".format(file_name.text + ':'))
        number_part = BeautifulSoup('<div style="display: flex; flex-direction: row;"></div>')
        for _ in range(4):
            part_lower = BeautifulSoup('<span>{}<span>{}</span></span>'.format(name_dict[counter % 4] + " ", numbers[counter].text + " | "))
            number_part.div.append(part_lower)
            counter+=1
        part.append(number_part)
        if(
            file_name.text != 'c++/5/bits' and 
            file_name.text != 'gtest' and
            file_name.text != 'c++/5' and
            file_name.text != 'gtest/internal' and
            file_name.text != '/usr/include/c++/5' and
            file_name.text != '/usr/include/c++/5/bits' and
            file_name.text != '/usr/include/gtest' and
            file_name.text != '/usr/include/gtest/internal'
        ):
            suop_new.div.append(part)

    with open("report.txt", "w") as f:
        f.write(suop_new.prettify())
