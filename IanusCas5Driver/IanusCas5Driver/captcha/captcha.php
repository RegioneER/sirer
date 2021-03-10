<?phpsession_start();

header("Content-type: image/png");

$image = imagecreate(60,20);

$background_color = ImageColorAllocate($image, rand(64,70), rand(70,73), rand(100,110));

$colour1 = ImageColorAllocate($image, rand(121,255), rand(126,255), rand(197,255));
$colour2 = ImageColorAllocate($image, rand(100,255), rand(120,255), rand(105,255));
$colour3 = ImageColorAllocate($image, rand(131,255), rand(137,255), rand(100,255));

imagestring($image,5,8,2,$_SESSION["captcha"],$colour1);
imagestring($image,5,8,2,$_SESSION["captcha"],$colour2);
imagestring($image,5,8,2,$_SESSION["captcha"],$colour3);

imageline($image, rand(1,300), rand(1,3), rand(10,150), rand(0,150), $colour1);
imageline($image, rand(1,300), rand(1,3), rand(10,150), rand(0,150), $colour2);
imageline($image, rand(1,300), rand(1,3), rand(10,150), rand(0,150), $colour3);

imageline($image, 10, 0, 14, 10, $colour1);
imageline($image, 20, 0, 24, 30, $colour2);
imageline($image, 55, 0, 34, 60, $colour3);

imagepng($image);

imagedestroy($image);?>