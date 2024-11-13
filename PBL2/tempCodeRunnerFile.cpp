void docFile(LinkList &l1, LinkList &l2, LinkList &l3,
             multimap<string, Product*>& products,
             multimap<string, Kho*>& khoMap,
             multimap<string, Manager*>& managers) {
    ifstream fileKho("kho.txt");
    ifstream fileProduct("product.txt");
    ifstream fileManager("manager.txt");
    while (!fileKho.eof()) {
        Kho *k = new Kho;
        k->docFile(fileKho, managers);  
        khoMap.insert({k->getID(), k});
        l2.insertNode(k);
    }
    while (!fileProduct.eof()) {
        Product *p = new Product;
        p->docFile(fileProduct, khoMap);  
        if (!p->getID().empty()) {  
        products.insert({p->getID(), p});
        l1.insertNode(p);
    } else {
        delete p;  
    }
    }
    while (!fileManager.eof()) {
        Manager *m = new Manager;
        m->docFile(fileManager);
        managers.insert({m->getID(), m});
        l3.insertNode(m);
    }
}
