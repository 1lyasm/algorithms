select stations.station_name,
    total_ons
from rail_ridership
    inner join stations on 
        stations.station_id == 
        rail_ridership.station_id
    inner join lines on
        lines.line_id ==
        rail_ridership.line_id
    inner join time_periods on 
        time_periods.time_period_id == 
        rail_ridership.time_period_id
where season == 'Fall 2019' and
    lines.line_name == 'Red Line' and
    time_periods.time_period_id == 'time_period_11' and
            direction == 1 and
    total_ons > (select avg(total_ons) as average
        from rail_ridership
            inner join stations on 
                stations.station_id == 
                rail_ridership.station_id
            inner join lines on
                lines.line_id ==
                rail_ridership.line_id
            inner join time_periods on 
                time_periods.time_period_id == 
                rail_ridership.time_period_id
        where season == 'Fall 2019' and
            lines.line_name == 'Red Line' and
            time_periods.time_period_id == 'time_period_11' and
            direction == 1)
group by stations.station_name
order by total_ons desc, stations.station_name asc