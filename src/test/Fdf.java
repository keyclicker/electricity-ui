package test;

class Element
{
    float R, U, I;
    Element prev, next;

    public Element(float r, Element prev, Element next) {
        R = r;
        this.prev = prev;
        this.next = next;
    }

    public Element(float r) {
        R = r;
    }

    public Element(Element prev, Element next) {
        this.prev = prev;
        this.next = next;
    }

    public float getR() {
        return R;
    }

    public void setR(float r) {
        R = r;
    }

    public float getU() {
        return U;
    }

    public void setU(float u) {
        U = u;
    }

    public float getI() {
        return I;
    }

    public void setI(float i) {
        I = i;
    }

    public Element getPrev() {
        return prev;
    }

    public void setPrev(Element prev) {
        this.prev = prev;
    }

    public Element getNext() {
        return next;
    }

    public void setNext(Element next) {
        this.next = next;
    }
}