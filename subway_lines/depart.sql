select stations.station_name, season, sum(total_offs)
from rail_ridership
    inner join stations
        on stations.station_id == rail_ridership.station_id
group by stations.station_name, season
order by sum(total_offs) desc,
    season, stations.station_name asc