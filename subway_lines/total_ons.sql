select season, line_id, direction, total_ons
from rail_ridership
    inner join stations
        on stations.station_id == rail_ridership.station_id
    inner join time_periods
        on time_periods.time_period_id == rail_ridership.time_period_id
where stations.station_name == 'Kendall/MIT'
    and time_periods.day_type == 'weekday'
    and time_periods.period_start_time == '16:00:00'
order by season, direction ASC