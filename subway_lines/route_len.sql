with
    filtered as 
    (
    select 
        *
    from
        station_orders
        inner join routes using(route_id)
    where
        routes.line_id != 'green'
    )
select
    route_id,
    direction,
    route_name,
    count(station_id) as station_count,
    sum(distance_from_last_station_miles) as route_len
from
    filtered
group by
    route_id
order by
    route_id asc