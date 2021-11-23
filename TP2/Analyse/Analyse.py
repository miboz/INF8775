import pandas as pd

df = pd.read_csv('results.csv')
# group by nb_nodes and algo and get mean of time
df_mean = df.groupby(['nb_nodes', 'algo']).mean()
# print df_mean when algo is 'glouton' and nb_nodes is 2
print(df_mean.loc[(2, 'glouton')])
#remove column 'seed'
df_mean = df_mean.drop('seed', 1)

txt = 'asdf/r/nasad'
# set 'algo' on position 31 in df_mean
df_mean.insert(31, 'algo', txt)

# get last n rows of df_mean
df_mean = df_mean.tail(10)
