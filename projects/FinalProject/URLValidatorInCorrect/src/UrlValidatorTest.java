

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   // should pass
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println(urlVal.isValid("http://10.0.0.225"));
	   System.out.println(urlVal.isValid("https://10.0.0.225"));
	   System.out.println(urlVal.isValid("ftp://10.0.0.225"));
	   System.out.println(urlVal.isValid("file://10.0.0.225"));
	   System.out.println(urlVal.isValid("http://10.0.0.225:32"));
	   System.out.println(urlVal.isValid("http://10.0.0.225:322"));
	   System.out.println(urlVal.isValid("http://10.0.0.225:3222"));
	   System.out.println(urlVal.isValid("http://10.0.0.225:3222"));
	   System.out.println(urlVal.isValid("https://google.com"));
	   System.out.println(urlVal.isValid("htp://www.google.com"));
	   System.out.println(urlVal.isValid("https://www.google.com"));
	   System.out.println(urlVal.isValid("ftp://www.google.com:102"));
	   System.out.println(urlVal.isValid("http://www.google.com?x=1"));
	   System.out.println(urlVal.isValid("http://www.google.com?x"));
	   System.out.println(urlVal.isValid("http://www.google.com?x\0"));
	   System.out.println(urlVal.isValid("http://www.google.com?x\n"));
	   System.out.println(urlVal.isValid("http://www.google.com:65535"));
	   System.out.println(urlVal.isValid("http://www.google.com:1024"));
	   System.out.println(urlVal.isValid("http://www.google.com?x=1"));
	   System.out.println(urlVal.isValid("http://www.google.com?x"));
	   System.out.println(urlVal.isValid("http://www.google.com?x\0"));
	   System.out.println(urlVal.isValid("http://www.google.com?x\n"));	   
	   System.out.println(urlVal.isValid("http://10.0.0.225:3000"));

   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
