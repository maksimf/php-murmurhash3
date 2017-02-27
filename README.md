# PHP MurmurHash3

*MurmurHash* is an algorithm desiged by Austin Appleby.

This is a fork of PHP extension authored by j42. The original extension didn't work correct with the certain data.

## Install

```bash
chmod +x build/install.sh
./build/install.sh
```

## Usage

```php
echo murmurhash3(key, seed);
```
