<?php

$background_color = ImageColorAllocate($image, rand(200,255),  rand(200,255),  rand(200,255));

$colour = ImageColorAllocate($image, rand(50,100), rand(60,100), rand(55,100));

imagestring($image,320,rand(19,25),rand(9,15),$stringa,$colour);

imageline($image, rand(1,300), rand(1,3), rand(10,150), rand(0,150), $colour);
imageline($image, rand(15,20), 0, rand(12,24), 30, $colour);

imagepng($image);

imagedestroy($image);