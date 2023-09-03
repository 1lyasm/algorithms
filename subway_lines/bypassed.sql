with
    filtered as
    (
    select
        line_id,
        direction,
        time_period_id,
        station_id,
        average_ons,
        average_offs,
        average_flow
    from
        rail_ridership
    where
        season = 'Fall 2019'
    ),
    summed as
    (
    select
        line_id,
        station_id,
        sum(average_ons) + sum(average_offs) as sum_on_offs,
        sum(average_flow) as sum_average_flow
    from
        filtered
    group by
        line_id,
        station_id
    )
select
    stations.station_name,
    lines.line_name,
    sum_average_flow,
    sum_on_offs
from
    (select
        station_id,
        line_id,
        sum_average_flow,
        sum_on_offs,
        max(sum_average_flow / cast(sum_on_offs as real)) as flow_over_onoffs
    from
        summed
    group by
        line_id)
    inner join stations using(station_id)
    inner join lines using(line_id)
order by
    line_name asc