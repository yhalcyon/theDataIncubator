# read and clean data
myData <- read.csv("dataScience.csv")
myData$num <- as.character(myData$num)
myData$num <- as.numeric(gsub(',','',myData$num))

# get geographical coordinates from zipcode
library(zipcode)
data(zipcode)
myData = merge(myData, zipcode, by.x='state', by.y='state')
myData = myData[!duplicated(myData$state), ]

# get a Google map with the range of United States
library(ggmap)
map<-get_map(location='united states', zoom=4, maptype = "terrain",
             source='google',color='color')

# plot the data
library("ggplot2")
library("RColorBrewer")
ggmap(map) + geom_point(
  aes(x=longitude, y=latitude, show_guide = TRUE, colour=num, size=num), 
  data=myData, na.rm = T) +
  scale_color_gradient(low="deepskyblue",high="blue") +
  scale_size_area(max_size = 20)