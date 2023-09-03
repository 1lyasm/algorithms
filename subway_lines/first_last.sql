select lines.line_name,
    direction_desc,
    first_stations.station_name,
    last_stations.station_name
from routes
    inner join lines on lines.line_id == routes.line_id
    inner join stations as first_stations
        on first_stations.station_id == routes.first_station_id
    inner join stations as last_stations
        on last_stations.station_id == routes.last_station_id
order by lines.line_name, direction_desc,
         first_stations.station_name,
         last_stations.station_name ASC;