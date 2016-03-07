PHPLocalizator is a PHP extension to resolve internationalization problem on the web projects.
This extension written in C++ based on the PHP-CPP library. For more information about PHP-CPP follow this link: http://www.php-cpp.com/

### Features

* Fast and easy access to the words or phrases in the custom xml files
* Less memory usage on big projects
* Ability to use variables in the phrase for different variation
 
### Requirements

* Install PHP-CPP library to be able to compile source code.


### Usage example

The XML files ierarchy example.

![alt tag](http://elshadaghazade.info/images/content/folder-ierarchy.jpg)

```php
// Creating the object
$var = new PHPLocalizator();
$var->setFolderPath("/var/www/mywebproject/localization")
    ->setLocale("ru-RU")
    ->setSpecialKey("{%w}");

// simple phrase
echo $var->get("ExampleFolder/example/first_word");
// phrase with one variable
echo $var->get("ExampleFolder/example/second_word", "Stive");
// phrase with two variable
echo $var->get("ExampleFolder/example/third_word", "Stive", "Jobs");

```