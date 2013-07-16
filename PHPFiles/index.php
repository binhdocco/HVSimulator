<?php 
//path to directory to scan
$directory = "";

//get all bundle files with a .bundle extension.
$texts = glob($directory . "*.zip");

echo "<?xml version='1.0' encoding='UTF-8'?>";
echo "<!DOCTYPE plist PUBLIC '-//Apple//DTD PLIST 1.0//EN' 'http://www.apple.com/DTDs/PropertyList-1.0.dtd'>";
echo "<plist version='1.0'>";
echo "<array>";
foreach($texts as $text)
{

    echo "<string>" . $text . "</string>";
}
echo "</array>";
echo "</plist>";
?>