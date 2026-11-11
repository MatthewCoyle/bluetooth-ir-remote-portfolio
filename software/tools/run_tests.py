"""Host verification only; does not compile against Arduino or IRremote."""
import argparse, pathlib, subprocess, json, sys
p=argparse.ArgumentParser();p.add_argument('--compiler',default='g++');p.add_argument('--report',type=pathlib.Path);a=p.parse_args()
root=pathlib.Path(__file__).resolve().parents[2]
build=root/'build';build.mkdir(exist_ok=True)
exe=build/('remote_tests.exe' if sys.platform=='win32' else 'remote_tests')
records=[]
for mode,extra in [('normal',[]),('ndebug',['-DNDEBUG'])]:
 command=[a.compiler,'-std=c++11','-Wall','-Wextra','-Werror','-pedantic']+extra+['-I'+str(root/'software/tests/fakes'),str(root/'software/tests/test_remote.cpp'),'-o',str(exe)]
 r=subprocess.run(command,text=True,capture_output=True)
 item={'mode':mode,'compile_exit':r.returncode,'compile_stdout':r.stdout,'compile_stderr':r.stderr}
 if r.returncode==0:
  t=subprocess.run([str(exe)],text=True,capture_output=True);item.update(run_exit=t.returncode,stdout=t.stdout,stderr=t.stderr)
 records.append(item)
 print(json.dumps(item,indent=2))
result={'compiler':subprocess.run([a.compiler,'--version'],capture_output=True,text=True).stdout.splitlines()[0],'results':records}
if a.report:a.report.write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
sys.exit(0 if all(r['compile_exit']==0 and r.get('run_exit')==0 for r in records) else 1)
