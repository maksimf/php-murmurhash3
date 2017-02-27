# PHP MurmurHash3

*MurmurHash* is an algorithm desiged by Austin Appleby.

This is a fork of PHP extension authored by [j42](https://github.com/j42/php-murmurhash3). The original extension didn't work correct with the certain data.

## Install

```bash
chmod +x build/install.sh
./build/install.sh
```

## Usage

```php
// Example
echo murmurhash3('豥붢㦖徱阵儹㜀耄巅簏罚撦', 1096928849); // 340060741
```
