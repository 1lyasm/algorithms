select stations.station_name, max(gated_entries)
from gated_station_entries
    inner join stations
        on stations.station_id ==
            gated_station_entries.station_id
where service_date like '2021-06-%'
group by stations.station_name
order by stations.station_name asc, gated_entries desc