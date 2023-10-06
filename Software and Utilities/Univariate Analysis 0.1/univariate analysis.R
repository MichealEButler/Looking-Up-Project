library(ggplot2)
library("plotrix")
library(HDInterval)
library(ggpubr)

data <- read.table("LSP_DTR_Finals.txt")

i_elevation <- read.table("Tweed/sites_elevation.txt")
i_dtr <- read.table("Tweed/sites_dtr.txt")
i_aspect <- read.table("Tweed/sites_aspect.txt")
i_slope <- read.table("Tweed/sites_slope.txt")
i_TRI <- read.table("Tweed/sites_TRI.txt")
i_vis <- read.table("Tweed/sites_vis.txt")
i_cost <- read.table("Tweed/sites_slope_cost.txt")


summary(data)
mean(data$V1, na.rm = TRUE)
dtr = data$V1

elevation = i_elevation$V1
dtr = i_dtr$V1
aspect = i_aspect$V1
slope = i_slope$V1
TRI = i_TRI$V1
vis = i_vis$V1
cost = i_cost$V1

Q90e = quantile(i_elevation$V1,na.rm = T,probs = c(0.9))
Q10e = quantile(i_elevation$V1,na.rm = T,probs = c(0.1)) #quantile lines

Q90d = quantile(i_dtr$V1,na.rm = T,probs = c(0.9))
Q10d = quantile(i_dtr$V1,na.rm = T,probs = c(0.1)) #quantile lines

Q90a = quantile(i_aspect$V1,na.rm = T,probs = c(0.9))
Q10a = quantile(i_aspect$V1,na.rm = T,probs = c(0.1)) #quantile lines

Q90s = quantile(i_slope$V1,na.rm = T,probs = c(0.9))
Q10s = quantile(i_slope$V1,na.rm = T,probs = c(0.1)) #quantile lines

Q90t = quantile(i_TRI$V1,na.rm = T,probs = c(0.9))
Q10t = quantile(i_TRI$V1,na.rm = T,probs = c(0.1)) #quantile lines

Q90v = quantile(i_vis$V1,na.rm = T,probs = c(0.9))
Q10v = quantile(i_vis$V1,na.rm = T,probs = c(0.1)) #quantile lines

Q90c = quantile(i_cost$V1,na.rm = T,probs = c(0.9))
Q10c = quantile(i_cost$V1,na.rm = T,probs = c(0.1)) #quantile lines

ggplot(i_elevation, aes(x=elevation)) + geom_density(fill = "blue", alpha = 0.2) + geom_vline(aes(xintercept=mean(elevation)),linetype = "longdash", size=0.8, color = "red") + geom_vline(xintercept = Q90e, linetype="dashed", size = 0.8) + geom_vline(xintercept = Q10e, linetype="dashed", size = 0.8)
summary(i_elevation)
print(Q90e)
print(Q10e)
std.error(i_elevation)
hdi(i_elevation, credMass = 0.9)
ggplot(i_elevation, aes(x=elevation)) + geom_density(fill = "blue", alpha = 0.2) + geom_vline(xintercept=hdi(i_elevation, credMass = 0.9),linetype="dashed", size=0.8)

ggplot(i_dtr, aes(x=dtr)) + geom_density(fill = "blue", alpha = 0.2) + geom_vline(aes(xintercept=mean(dtr)),linetype = "longdash", size=0.8, color = "red") + geom_vline(xintercept = Q90d, linetype="dashed", size = 0.8) + geom_vline(xintercept = Q10d,linetype="dashed", size = 0.8)
summary(i_dtr)
print(Q90d)
print(Q10d)
std.error(i_dtr)
hdi(i_dtr, credMass = 0.9)
ggplot(i_dtr, aes(x=dtr)) + geom_density(fill = "blue", alpha = 0.2) + geom_vline(xintercept=hdi(i_dtr, credMass = 0.9),linetype="dashed", size=0.8)

ggplot(i_aspect, aes(x=aspect)) + geom_density(fill = "blue", alpha = 0.2) + geom_vline(aes(xintercept=mean(aspect)),linetype="longdash", size=0.8, color = "red") + geom_vline(xintercept = Q90a, linetype="dashed", size = 0.8) + geom_vline(xintercept = Q10a, linetype="dashed", size = 0.8)
summary(i_aspect)
print(Q90a)
print(Q10a)
std.error(i_aspect)
hdi(i_aspect, credMass = 0.9)
ggplot(i_aspect, aes(x=aspect)) + geom_density(fill = "blue", alpha = 0.2) + geom_vline(xintercept=hdi(i_aspect, credMass = 0.9),linetype="dashed", size=0.8)

ggplot(i_slope, aes(x=slope)) + geom_density(fill = "blue", alpha = 0.2) + geom_vline(aes(xintercept=mean(slope)),linetype="longdash", size=0.8, color = "red") + geom_vline(xintercept = Q90s, linetype="dashed", size = 0.8) + geom_vline(xintercept = Q10s, linetype="dashed", size = 0.8)
summary(i_slope)
print(Q90s)
print(Q10s)
std.error(i_slope)
hdi(i_slope, credMass = 0.9)
ggplot(i_slope, aes(x=slope)) + geom_density(fill = "blue", alpha = 0.2) + geom_vline(xintercept=hdi(i_slope, credMass = 0.9),linetype="dashed", size=0.8)

ggplot(i_TRI, aes(x=TRI)) + geom_density(fill = "blue", alpha = 0.2) + geom_vline(aes(xintercept=mean(TRI)),linetype="longdash", size=0.8, color = "red") + geom_vline(xintercept = Q90t, linetype="dashed", size = 0.8) + geom_vline(xintercept = Q10t, linetype="dashed", size = 0.8)
summary(i_TRI)
print(Q90t)
print(Q10t)
std.error(i_TRI)
hdi(i_TRI, credMass = 0.9)
ggplot(i_TRI, aes(x=TRI)) + geom_density(fill = "blue", alpha = 0.2) + geom_vline(xintercept=hdi(i_TRI, credMass = 0.9),linetype="dashed", size=0.8)
median_mad(TRI)

ggplot(i_vis, aes(x=vis)) + geom_density(fill = "blue", alpha = 0.2) + geom_vline(aes(xintercept=mean(vis)),linetype="longdash", size=0.8, color = "red") + geom_vline(xintercept = Q90v, linetype="dashed", size = 0.8) + geom_vline(xintercept = Q10v, linetype="dashed", size = 0.8)
summary(i_vis)
print(Q90v)
print(Q10v)
std.error(i_vis)
hdi(i_vis, credMass = 0.9)
ggplot(i_vis, aes(x=vis)) + geom_density(fill = "blue", alpha = 0.2) + geom_vline(xintercept=hdi(i_vis, credMass = 0.9),linetype="dashed", size=0.8)
median_mad(vis)

ggplot(i_cost, aes(x=cost)) + geom_density(fill = "blue", alpha = 0.2) + geom_vline(aes(xintercept=mean(cost)),linetype="longdash", size=0.8, color = "red") + geom_vline(xintercept = Q90c, linetype="dashed", size = 0.8) + geom_vline(xintercept = Q10c, linetype="dashed", size = 0.8)
summary(i_cost)
print(Q90c)
print(Q10c)
std.error(i_cost)
hdi(i_cost, credMass = 0.9)
ggplot(i_cost, aes(x=cost)) + geom_density(fill = "blue", alpha = 0.2) + geom_vline(xintercept=hdi(i_cost, credMass = 0.9),linetype="dashed", size=0.8)
median_mad(cost)
  
