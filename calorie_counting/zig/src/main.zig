const std = @import("std");

fn readInt(str: []const u8, curIndex: *i32) i32 {
    var number: i32 = 0;
    var end: i32 = curIndex.*;
    var factor: i32 = 1;
    while (end >= 0 and str[@intCast(end)] != '\n') {
        number += factor * (str[@intCast(end)] - '0');
        factor *= 10;
        end -= 1;
    }
    curIndex.* = end - 1;
    return number;
}

fn sumGroup(str: []const u8, curIndex: *i32) i32 {
    var sum: i32 = 0;
    var end: i32 = curIndex.*;
    while (end >= 0 and str[@intCast(end)] != '\n') {
        sum += readInt(str, &end);
    }
    curIndex.* = end - 1;
    return sum;
}

fn maxCalories(str: []const u8) i32 {
    var curIndex: i32 = @intCast(str.len - 1);
    var maxSum: i32 = -1;
    var sum: i32 = -1;
    while (curIndex >= 0) {
        sum = sumGroup(str, &curIndex);
        if (sum > maxSum) {
            maxSum = sum;
        }
    }
    return maxSum;
}

pub fn main() !void {
    const stdout = std.io.getStdOut().writer();
    var file = try std.fs.cwd().openFile("src/input.txt", std.fs.File.OpenFlags{ .mode = std.fs.File.OpenMode.read_only });
    defer file.close();

    const maxBytes = 1e6;
    const allocator = std.heap.page_allocator;

    var str = try file.readToEndAlloc(allocator, maxBytes);
    defer allocator.free(str);

    try stdout.print("{d}\n", .{maxCalories(str)});
}
