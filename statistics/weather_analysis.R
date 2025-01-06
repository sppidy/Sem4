# Load necessary libraries
library(dplyr)
library(ggplot2)

# Load the dataset
weather_data <- read.csv("c:/Users/scope1/Documents/final_weather_data.csv")

# Rename columns to remove special characters
colnames(weather_data) <- c("Date", "Weather_Condition", "Dew_Point_C", "Humidity", "Pressure_hPa", "Temperature_C", "Visibility_km", "Wind_Direction_Compass", "Rain_Presence")

# 1. Separate the dataset on the basis of weather condition and find the average temperature for each condition
avg_temp_by_condition <- weather_data %>%
  group_by(Weather_Condition) %>%
  summarise(avg_temp = mean(Temperature_C, na.rm = TRUE))

# Find the Weather Condition with the highest average temperature
max_avg_temp <- avg_temp_by_condition %>%
  filter(avg_temp == max(avg_temp))

print(max_avg_temp)

# 2. Which wind direction (Compass) was most frequently observed?
most_frequent_wind_direction <- weather_data %>%
  count(Wind_Direction_Compass) %>%
  arrange(desc(n)) %>%
  slice(1)

print(most_frequent_wind_direction)

# 3. Calculate the median visibility recorded in the dataset
median_visibility <- median(weather_data$Visibility_km, na.rm = TRUE)
print(median_visibility)

# 4. What is the average humidity recorded across all days (closest value)
avg_humidity <- mean(weather_data$Humidity, na.rm = TRUE)
print(avg_humidity)

# 5. Which day recorded the highest temperature?
highest_temp_day <- weather_data %>%
  filter(Temperature_C == max(Temperature_C, na.rm = TRUE))

print(highest_temp_day)

# 6. Comment on mode for the feature "weather condition" and "Wind direction"
weather_condition_mode <- weather_data %>%
  count(Weather_Condition) %>%
  arrange(desc(n)) %>%
  slice(1)

wind_direction_mode <- weather_data %>%
  count(Wind_Direction_Compass) %>%
  arrange(desc(n)) %>%
  slice(1)

print(weather_condition_mode)
print(wind_direction_mode)

# 7. Plot all possible plots like bar graph, pie chart, box plot

# Bar graph for average temperature by weather condition
bar_plot <- ggplot(avg_temp_by_condition, aes(x = Weather_Condition, y = avg_temp)) +
  geom_bar(stat = "identity") +
  theme(axis.text.x = element_text(angle = 90, hjust = 1)) +
  labs(title = "Average Temperature by Weather Condition", x = "Weather Condition", y = "Average Temperature (°C)")
print(bar_plot)  # Print the plot

# Pie chart for wind direction frequency
wind_direction_freq <- weather_data %>%
  count(Wind_Direction_Compass)

pie_chart <- ggplot(wind_direction_freq, aes(x = "", y = n, fill = Wind_Direction_Compass)) +
  geom_bar(stat = "identity", width = 1) +
  coord_polar("y") +
  labs(title = "Wind Direction Frequency", x = "", y = "")
print(pie_chart)  # Print the plot

# Box plot for visibility
box_plot_visibility <- ggplot(weather_data, aes(x = "", y = Visibility_km)) +
  geom_boxplot() +
  labs(title = "Box Plot of Visibility", x = "", y = "Visibility (km)")
print(box_plot_visibility)  # Print the plot

# Box plot for temperature by weather condition
box_plot_temp <- ggplot(weather_data, aes(x = Weather_Condition, y = Temperature_C)) +
  geom_boxplot() +
  theme(axis.text.x = element_text(angle = 90, hjust = 1)) +
  labs(title = "Box Plot of Temperature by Weather Condition", x = "Weather Condition", y = "Temperature (°C)")
print(box_plot_temp)  # Print the plot
