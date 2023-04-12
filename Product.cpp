#include "Product.h"

void Product::setProductAttributes(string new_PLU, string new_name, int new_type, double new_price, int new_inventory) {
  PLU = new_PLU;
  name = new_name;
  type = new_type;
  price = new_price;
  inventory = new_inventory;
}

void Product::setInventory(int new_inventory) {
  inventory = new_inventory;
}

string Product::getPLU() const {
  return PLU;
}

string Product::getName() const {
  return name;
}

int Product::getType() const {
  return type;
}

double Product::getPrice() const {
  return price;
}

int Product::getInventory() const {
  return inventory;
}
