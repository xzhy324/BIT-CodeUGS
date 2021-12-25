import pandas as pd
import numpy as np

# 读取文章
df = pd.DataFrame(pd.read_excel("./Corpus/data1.xlsx",engine='openpyxl',sheet_name=2))
print(df.values)