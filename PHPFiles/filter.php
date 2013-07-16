<?php 
//path to directory to scan
$directory = "";

//get all bundle files with a .bundle extension.
$texts = glob($directory . "*.zip");
$filters = array();
foreach($texts as $text)
{
	$temp = explode("_", $text);
	//echo $temp[2];
	if (!in_array($temp[2], $filters)) {
		array_push($filters,$temp[2]);
	}
}

echo "<?xml version='1.0' encoding='UTF-8'?>";
echo "<!DOCTYPE plist PUBLIC '-//Apple//DTD PLIST 1.0//EN' 'http://www.apple.com/DTDs/PropertyList-1.0.dtd'>";
echo "<plist version='1.0'>";
echo "<array>";
echo "<string>" . "ALL" . "</string>";
foreach($filters as $text)
{

    echo "<string>" . $text . "</string>";
}
echo "</array>";
echo "</plist>";
?>