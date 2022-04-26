#!/usr/bin/python3

import os
import os.path
import re


if __name__ == "__main__":
  total_solve = len([name for name in os.listdir('solves/')
                     if os.path.isfile(os.path.join('solves/', name)) and not name.startswith('.')])
  with open("README.md", "r") as f:
    lines = f.readlines()
  for ix in range(len(lines)):
    if lines[ix].startswith('![](https://img.shields.io/badge/Total_solves-'):
      lines[ix] = f"![](https://img.shields.io/badge/Total_solves-{total_solve}_/_100-blueviolet.svg)\n"
  with open("README.md", "w") as f:
    f.writelines(lines)
