SELECT station_id, route_id, distance_from_last_station_miles
FROM station_orders
WHERE distance_from_last_station_miles > 1
ORDER BY distance_from_last_station_miles DESC,
         route_id, station_id ASC