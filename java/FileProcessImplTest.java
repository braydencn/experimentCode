import static org.junit.Assert.*;

import org.junit.Test;


public class FileProcessImplTest {

	@Test
	public void testProcessByLine() {
		final StringBuilder sb=new StringBuilder();
		final StringBuilder sb1=new StringBuilder();
		FileProcessor fp=new FileProcessorImpl();
		
		fp.processByLine("a.txt", new LineProcessor(){
			@Override
			public void doSomeThing(String oneLine) {
				sb.append(oneLine);
			}
		});
		
		fp.processByLine("a_reverse_by_line.txt", new LineProcessor(){
			@Override
			public void doSomeThing(String oneLine) {
				sb1.append(new StringBuilder(oneLine).reverse());
			}
		});
		
		assertEquals(sb.toString(), sb1.toString());
	}

}
