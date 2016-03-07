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

The xml file structure should looks like this:

```xml
<?xml version="1.0" encoding="utf-8"?>
    <contents>
        <description>This file keeps sample messages</description>
        <element>
            <name>first_word</name>
            <value>You are welcome!</value>
        </element>
        <element>
            <name>second_word</name>
            <value>Dear {%w}, You are welcome!</value>
        </element>
        <element>
            <name>third_word</name>
            <value>Dear {%w} {%w}, You are welcome!</value>
        </element>
        ....
    </contents>
```

How to use in PHP:

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

Example video: [https://www.youtube.com/watch?v=YJkRfH4Dq2I](https://www.youtube.com/watch?v=YJkRfH4Dq2I)

## Related links
* See documentation of PHP-CPP library: <a href="http://www.php-cpp.com/documentation">PHP-CPP documentation</a>
* PHPLocalizator related article: <a href="http://elshadaghazade.info/blog/internationalization-at-the-PHP-projects-PHPLocalizator-extension-introduction-VIDEO/">INTERNATIONALIZATION AT THE PHP PROJECTS (PHPLOCALIZATOR EXTENSION INTRODUCTION) + VIDEO</a>
