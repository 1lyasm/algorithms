select time_periods.day_type,
    time_periods.period_start_time,
    season,
    line_id,
    stations.station_name,
    max(total_ons)
from rail_ridership
    inner join time_periods
        on time_periods.time_period_id ==
        rail_ridership.time_period_id
    inner join stations
        on stations.station_id ==
            rail_ridership.station_id
group by line_id,
    time_periods.day_type
order by total_ons desc