public class test{
    static Book[] newBookArr(Book b1,Book b2){
        b1.price=250;
        return new Book[]{b2,b1};
    }
    public static void main(String[] argv){
        Book a=new Book(300);
        Book[] b=newBookArr(a, new Book(200));
        System.out.println(a.price+" ");
        b[0]=a;
        for(int x=0;x<2;x++)
        System.out.print(b[x].price+" ");
    }
}
class Book{
    int price;
    public Book(int p){price=p;}
}