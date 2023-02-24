#include "order.h"
#include "fileio.h"

void Order::write(std::ostream& os) const {
    write_pod(os, id_);
    write_pod(os, customer_id_);
    write_string(os, item_);
    write_pod(os, quantity_);
    write_string(os, order_date_);
    write_string(os, delivery_date_);
}

void Order::read(std::istream& is) {
    id_ = read_pod<int>(is);
    customer_id_ = read_pod<int>(is);
    item_ = read_string(is);
    quantity_ = read_pod<int>(is);
    order_date_ = read_string(is);
    delivery_date_ = read_string(is);
}

