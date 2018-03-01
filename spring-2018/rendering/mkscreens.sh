TYPE=rtr
SCREEN_RES=512x384
THUMB_RES=128x96

convert $1 -resize $SCREEN_RES $TYPE-homework$2-screenshot-$SCREEN_RES.png
convert $1 -resize $THUMB_RES $TYPE-homework$2-thumbnail-$THUMB_RES.png
