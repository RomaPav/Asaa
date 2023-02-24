#include "customer.h"
#include "fileio.h"

void Customer::write(std::ostream& os) const {
    write_pod(os, id_);
    write_string(os, name_);
    write_string(os, email_);
    write_string(os, phone_);
    write_string(os, address_);
}

void Customer::read(std::istream& is) {
    id_ = read_pod<int>(is);
    name_ = read_string(is);
    email_ = read_string(is);
    phone_ = read_string(is);
    address_ = read_string(is);
}
