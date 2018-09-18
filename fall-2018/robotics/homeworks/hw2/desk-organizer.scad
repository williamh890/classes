dim=[80, 40, 20];

width = dim[0];
depth = dim[1];
height = dim[2];

wall = 1;
drawer_width = dim[0] / 2 - 2.*wall;

organizer();

module organizer() {

organizer_body();

drawer_slop = 1;
drawer_offset = 20;

translate([wall + drawer_slop / 2, wall+drawer_offset, wall + drawer_slop / 2])
    organizer_drawer(inner_wall=1, slop=drawer_slop);

translate([width / 2 + .5*wall, wall + drawer_offset - 10, wall])
    organizer_drawer(inner_wall=1, slop=drawer_slop);
}

module organizer_body() {

difference() {
    cube([width, depth, height]);

    drawer_cutout = [
        drawer_width,
        2+depth - wall,
        height - 2*wall
    ];

    translate([wall, wall, wall])
        cube(drawer_cutout);
    translate([width / 2 + .5*wall, wall, wall])
        cube(drawer_cutout);
}

}

module organizer_drawer(inner_wall, slop) {

difference(){
    cube([drawer_width-slop, depth - wall-slop, height-2*wall-slop]);

    translate([inner_wall, inner_wall, inner_wall])
        cube([
            drawer_width-2*inner_wall-slop,
            depth-wall-2*inner_wall-slop,
            height-2*wall
        ]);
}
}




