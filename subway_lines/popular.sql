create index my_index on
    gated_station_entries(station_id,
    line_id, gated_entries);
explain query plan with
    summed as 
    (select
        station_id,
        line_id,
        sum(gated_entries) as agg_gated_entries
    from
        gated_station_entries
    group by station_id, line_id
    ),
    filtered_station_orders as (
        select
            route_id,
            station_id,
            stop_order
        from
            station_orders
    ),
    aggregated as
    (select
        station_id,
        line_id,
        agg_gated_entries,
        route_id,
        stop_order
    from
        summed
        inner join filtered_station_orders using(station_id)
    ),
    popular as
    (select
        line_id,
        station_id,
        max(agg_gated_entries) as pop_gated_entries,
        route_id,
        stop_order
    from
        aggregated
    group by
        route_id,
        line_id
    )
select distinct
    lines.line_name,
    pop_stations.station_name,
    agg_stations.station_name,
    agg_gated_entries
from
    aggregated
    inner join popular using(line_id,route_id)
    inner join lines using(line_id)
    inner join stations as pop_stations on
        pop_stations.station_id == popular.station_id
    inner join stations as agg_stations on
        agg_stations.station_id == aggregated.station_id
where 
    aggregated.stop_order != popular.stop_order and
    aggregated.stop_order >= popular.stop_order - 2 and
    aggregated.stop_order <= popular.stop_order + 2
order by
    lines.line_name,
    pop_stations.station_name,
    agg_stations.station_name asc