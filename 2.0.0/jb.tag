<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>jb_config.h</name>
    <path>/home/burguete/programas/jb/2.0.0/</path>
    <filename>jb__config_8h.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>JB_DEBUG_FILE</name>
      <anchorfile>jb__config_8h.html</anchorfile>
      <anchor>a7195195dd577839a3644c6003ba94ae2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JB_BUFFER_SIZE</name>
      <anchorfile>jb__config_8h.html</anchorfile>
      <anchor>a3f591dda11b9cc92c27650fb2cf73afa</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FRS</name>
      <anchorfile>jb__config_8h.html</anchorfile>
      <anchor>a267822d1d6d8b84dbff0c6b0e06fd250</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBM_INTEGRAL_GAUSS_N</name>
      <anchorfile>jb__config_8h.html</anchorfile>
      <anchor>a37cd2aaffaa8ecd083af3dad60bfde51</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBW_GRAPHIC_N_TICS</name>
      <anchorfile>jb__config_8h.html</anchorfile>
      <anchor>a293d2e9a3087cd051cba1a3a86702e94</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBW_GRAPHIC_N_CHARS</name>
      <anchorfile>jb__config_8h.html</anchorfile>
      <anchor>a55b7b155af67b615dc833ae1780caf3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBW_GRAPHIC_FONT_SIZE</name>
      <anchorfile>jb__config_8h.html</anchorfile>
      <anchor>ab8fa8ea30265dd98d2764a35644a1f45</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBW_GRAPHIC_OUTPUT</name>
      <anchorfile>jb__config_8h.html</anchorfile>
      <anchor>a6a740933295917b5ac4177d924d77e90</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBW_OPEN_GL_OLD</name>
      <anchorfile>jb__config_8h.html</anchorfile>
      <anchor>ae3c392c552de0e0e5bc55bc2f8ea3a87</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>jb_def.c</name>
    <path>/home/burguete/programas/jb/2.0.0/</path>
    <filename>jb__def_8c.html</filename>
    <includes id="jb__def_8h" name="jb_def.h" local="yes" imported="no">jb_def.h</includes>
    <member kind="function">
      <type>void</type>
      <name>jb_free_null</name>
      <anchorfile>jb__def_8c.html</anchorfile>
      <anchor>a65e0a14c5a9cb93010f0e7eeb2fabc29</anchor>
      <arglist>(void **p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_function_null</name>
      <anchorfile>jb__def_8c.html</anchorfile>
      <anchor>aee69786a0d5743de9444b2dafa065497</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>jb_realloc</name>
      <anchorfile>jb__def_8c.html</anchorfile>
      <anchor>a3844e8db166174d1f750fdd035ea99fd</anchor>
      <arglist>(void *p, const int n)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>jb_strdup</name>
      <anchorfile>jb__def_8c.html</anchorfile>
      <anchor>ac4639dfa5ccc7cabfa20351a3de63eb7</anchor>
      <arglist>(char *buffer)</arglist>
    </member>
    <member kind="function">
      <type>long int</type>
      <name>jb_flength</name>
      <anchorfile>jb__def_8c.html</anchorfile>
      <anchor>a71cc918a6e8cdfea726cb128437a062a</anchor>
      <arglist>(FILE *file)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_slist_free</name>
      <anchorfile>jb__def_8c.html</anchorfile>
      <anchor>a11af508c4493432a70d2036e8f9502fc</anchor>
      <arglist>(GSList **list)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>jb_bin_read</name>
      <anchorfile>jb__def_8c.html</anchorfile>
      <anchor>a8537e30054c1d641136b63cbcc699d8d</anchor>
      <arglist>(FILE *file, char *buffer)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_bin_write</name>
      <anchorfile>jb__def_8c.html</anchorfile>
      <anchor>a4a0ab15e88b04e78933f239ed26355cf</anchor>
      <arglist>(FILE *file, char *buffer)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>jb_get_ncores</name>
      <anchorfile>jb__def_8c.html</anchorfile>
      <anchor>a61f3abc5632723515974bd3a1767b035</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>jb_def.h</name>
    <path>/home/burguete/programas/jb/2.0.0/</path>
    <filename>jb__def_8h.html</filename>
    <includes id="jb__config_8h" name="jb_config.h" local="yes" imported="no">jb_config.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>JBW_NO</name>
      <anchorfile>jb__def_8h.html</anchorfile>
      <anchor>ab3d7cc2955e72b9fdbbb9e27f9e5b17b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBW_GTK</name>
      <anchorfile>jb__def_8h.html</anchorfile>
      <anchor>a29f889ec23486f97b6ddad760bf184b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBW_GRAPHIC_OUTPUT_GDKPIXBUF</name>
      <anchorfile>jb__def_8h.html</anchorfile>
      <anchor>a175d065c66f9aed196d660f43c260108</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBW_GRAPHIC_OUTPUT_PNG</name>
      <anchorfile>jb__def_8h.html</anchorfile>
      <anchor>a3efb907eb9ddffbc073938802b8c3ef1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JB_PROTECT</name>
      <anchorfile>jb__def_8h.html</anchorfile>
      <anchor>a0a83fac32d093c45709583f194c4bbf2</anchor>
      <arglist>(a, b, c)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JB_POINTER_SIZE</name>
      <anchorfile>jb__def_8h.html</anchorfile>
      <anchor>ac7f46a1239840b4e3fffa79c54296af5</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JB_CHANGE</name>
      <anchorfile>jb__def_8h.html</anchorfile>
      <anchor>a95575b16c721540dd59ad9ee4e7ada75</anchor>
      <arglist>(a, b, c)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>jb_change</name>
      <anchorfile>jb__def_8h.html</anchorfile>
      <anchor>a7ffb39efe1e64fb1e394495ec71bc94d</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_function_null</name>
      <anchorfile>jb__def_8h.html</anchorfile>
      <anchor>aee69786a0d5743de9444b2dafa065497</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_free_null</name>
      <anchorfile>jb__def_8h.html</anchorfile>
      <anchor>aa6db1971713fa020bedec4d819013a16</anchor>
      <arglist>(void **)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>jb_realloc</name>
      <anchorfile>jb__def_8h.html</anchorfile>
      <anchor>a186dbb26b882d741225298860c9d3342</anchor>
      <arglist>(void *, const int)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>jb_strdup</name>
      <anchorfile>jb__def_8h.html</anchorfile>
      <anchor>a2f062e8ded0724aa519f90b48598fc5d</anchor>
      <arglist>(char *)</arglist>
    </member>
    <member kind="function">
      <type>long int</type>
      <name>jb_flength</name>
      <anchorfile>jb__def_8h.html</anchorfile>
      <anchor>a71cc918a6e8cdfea726cb128437a062a</anchor>
      <arglist>(FILE *file)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_slist_free</name>
      <anchorfile>jb__def_8h.html</anchorfile>
      <anchor>a11af508c4493432a70d2036e8f9502fc</anchor>
      <arglist>(GSList **list)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>jb_bin_read</name>
      <anchorfile>jb__def_8h.html</anchorfile>
      <anchor>a8537e30054c1d641136b63cbcc699d8d</anchor>
      <arglist>(FILE *file, char *buffer)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_bin_write</name>
      <anchorfile>jb__def_8h.html</anchorfile>
      <anchor>a4a0ab15e88b04e78933f239ed26355cf</anchor>
      <arglist>(FILE *file, char *buffer)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>jb_get_ncores</name>
      <anchorfile>jb__def_8h.html</anchorfile>
      <anchor>a61f3abc5632723515974bd3a1767b035</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>jb_math.c</name>
    <path>/home/burguete/programas/jb/2.0.0/</path>
    <filename>jb__math_8c.html</filename>
    <includes id="jb__math_8h" name="jb_math.h" local="yes" imported="no">jb_math.h</includes>
    <member kind="function">
      <type>void</type>
      <name>jbm_index_sort_flash</name>
      <anchorfile>jb__math_8c.html</anchorfile>
      <anchor>a58a30fb4e3dfd7a5c679e4c35a7d623d</anchor>
      <arglist>(JBFLOAT *x, int *ni, int n)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jbm_index_sort_flashl</name>
      <anchorfile>jb__math_8c.html</anchorfile>
      <anchor>a02fcae2b86992df90324fb67324307c7</anchor>
      <arglist>(JBDOUBLE *x, int *ni, int n)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>jb_math.h</name>
    <path>/home/burguete/programas/jb/2.0.0/</path>
    <filename>jb__math_8h.html</filename>
    <includes id="jb__def_8h" name="jb_def.h" local="yes" imported="no">jb_def.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>M_PIl</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a126570edaffa4fa37291be26b3b8fdce</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>M_LN10l</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>ace0f0f1f1d84eb88ab7b7b5f0d28dc6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBFLOAT</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>aee4bb77379861933a8e1b186114bb4a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ACOS</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>ac0968392c2b2fc716807863a5fa7d5f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CBRT</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a5c288402d0d0421758d773118c9f3df8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CEIL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>ae942a914db9767fa4fde805a268004e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>COS</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>af1af2de870caad797b91210f0fc6fe78</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXP</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a84db90500a1f9527c04e28817d9f60a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXP10</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a474918668c86ddd7746cb40ba179c39c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FABS</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>af0175ba905b01f1a4ba753b6961473c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FLOOR</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a1082f0d0b3b2f687958ea044cb0cd306</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FMAX</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>af9520fdf42fc2eb129de2c594eb10505</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FMIN</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>ada833912af53cace168f9be352e7cf7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOG</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a159ca84d25a5487d8e81e4438725df19</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOG10</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a386bc1bec332d5809e3c5e5be1f47a5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SQRT</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a095e93222540fb38e433670cf08b5a46</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FRF</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a16bb5201c0534fcdf25f6a313efc67e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FWF</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>aeb6959a71830652fe4b510ebac9b6ef8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPF</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a703b4f81abadf5e673e21656cedb1bdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FGF</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>ab87b744e146dffcc76e321ced743c451</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JB_EPSILON</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>ace2e63ffc2a3fc6962597fa0c8059782</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JB_PI</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>aae0a4929533a4e4f72cf93c11fda95af</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBDOUBLE</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a6fb87bb83b74f3fcb5500ad0da354427</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ACOSL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>af8dd9d8788c13df3ce5b4b36d8b7dd51</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CBRTL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a2803c2d7bc714387f94973e1a139f6c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CEILL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>aedf1d2f908596ad8949fa5bbb2d0a109</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>COSL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>aaf8e3fc97468c98b43e8ee764d1ac6f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXPL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a0499768a219eb7cb0379840b8dd3cb8e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXP10L</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a88942b5411d523df6172add9bd9ac3c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FABSL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a11143a7ba60f251554ab010ab0024336</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FLOORL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>af5facfad6fb7b437a2b6bcd33ea40550</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FMAXL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a93b8b28e1031ff19f1fa2154a84a4ba9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FMINL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a3d0730fc2b03f72701795772b9b020b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOGL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>ad158c6cedd8d338d3457740e94275bca</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LOG10L</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>afde259004fe244a8c438cfcef9a0d052</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SQRTL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>ad5e7b76412860410b7fb32d82ee96449</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JB_EPSILONL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a8c9d46d0280cf3a55f188a5fd999dfc7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JB_PIL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>ab21cb2caec1d757c4a2f45ef2ce0f62c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FRL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>ade892f2fa8a85504e18df4276e7f6691</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FWL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a85d207fe03e592efe8f9e5c4d1fbf3f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FPL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>afad4f9b38d52247fbb5780387e40a2e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FGL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>aa457977f67caa8ad10862b47a7a02d25</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FG_LENGTH</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a0a2379e0a17f99ad686e8e435073aec8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FWF2</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>aaaf2cdce809125954b015ea5401c4b1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBM_G</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>ab1e6f9cf258fb2aef137c4d3440f4daf</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBM_INDEX_SORT_FLASH_MIN</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a806d21034e9a3a8ddd71e16f9283b250</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBM_INDEX_SORT_MERGE_MIN</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a32cb26b043b5ff4a9b48bc75add47346</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBM_MAX</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a2f4f490f18bf2695b37ebf6d2371589a</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBM_MIN</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a2f4349b2f87c61814e99cd5b912b74d8</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBM_MODMIN</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>aa80eba78509f9c1073c2a36d9419a6ca</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBM_MODMINL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>add04cb67ba7034458ea11b6f2240aa0b</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBM_MODMINLL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>ad38664d115308f8547f872565fe4085f</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBM_FMODMIN</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a97ec895c505d1d4b63da9acdf8dbb1c6</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBM_FMODMINL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a9735bf2778c72d2018a0f8e9ab95baf0</anchor>
      <arglist>(a, b)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBM_SQR</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>ad96f621b3be91244e3d9c9f95b2fa90a</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBM_DBL</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>aaf2f56cbd7f239ec4e184d1ab0c57612</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>JBM_EXTRAPOLATE</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a7717ba50880c8e265c7b2caea3330602</anchor>
      <arglist>(x, x1, x2, y1, y2)</arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>JBMFluxLimiterType</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>ac5536321f8ec5bb095ea6703280a45b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jbm_index_sort_flash</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a58a30fb4e3dfd7a5c679e4c35a7d623d</anchor>
      <arglist>(JBFLOAT *x, int *ni, int n)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jbm_index_sort_flashl</name>
      <anchorfile>jb__math_8h.html</anchorfile>
      <anchor>a02fcae2b86992df90324fb67324307c7</anchor>
      <arglist>(JBDOUBLE *x, int *ni, int n)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>jb_win.c</name>
    <path>/home/burguete/programas/jb/2.0.0/</path>
    <filename>jb__win_8c.html</filename>
    <includes id="jb__win_8h" name="jb_win.h" local="yes" imported="no">jb_win.h</includes>
  </compound>
  <compound kind="file">
    <name>jb_win.h</name>
    <path>/home/burguete/programas/jb/2.0.0/</path>
    <filename>jb__win_8h.html</filename>
    <includes id="jb__math_8h" name="jb_math.h" local="yes" imported="no">jb_math.h</includes>
  </compound>
  <compound kind="file">
    <name>jb_xml.c</name>
    <path>/home/burguete/programas/jb/2.0.0/</path>
    <filename>jb__xml_8c.html</filename>
    <includes id="jb__xml_8h" name="jb_xml.h" local="yes" imported="no">jb_xml.h</includes>
    <member kind="function">
      <type>JBDOUBLE</type>
      <name>jb_xml_node_get_float</name>
      <anchorfile>jb__xml_8c.html</anchorfile>
      <anchor>a57dc497a5b5947c66a2b66a7e7be6d0f</anchor>
      <arglist>(xmlNode *node, const xmlChar *prop, int *error)</arglist>
    </member>
    <member kind="function">
      <type>JBDOUBLE</type>
      <name>jb_xml_node_get_float_with_default</name>
      <anchorfile>jb__xml_8c.html</anchorfile>
      <anchor>af4419d95252128b32adadb08c5b51904</anchor>
      <arglist>(xmlNode *node, const xmlChar *prop, int *error, JBDOUBLE def)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_xml_node_set_float_with_format</name>
      <anchorfile>jb__xml_8c.html</anchorfile>
      <anchor>a7abfd647de0bacffdd5af4f913ead3c9</anchor>
      <arglist>(xmlNode *node, const xmlChar *prop, char *format, JBDOUBLE x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_xml_node_set_float</name>
      <anchorfile>jb__xml_8c.html</anchorfile>
      <anchor>a34ef14fad6bed2c24e1f6b281507cc57</anchor>
      <arglist>(xmlNode *node, const xmlChar *prop, JBDOUBLE x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_xml_node_set_float_with_default</name>
      <anchorfile>jb__xml_8c.html</anchorfile>
      <anchor>aaa7fbe89a4393f2e5640fefd0baf4401</anchor>
      <arglist>(xmlNode *node, const xmlChar *prop, JBDOUBLE x, JBDOUBLE def)</arglist>
    </member>
    <member kind="function">
      <type>long int</type>
      <name>jb_xml_node_get_int</name>
      <anchorfile>jb__xml_8c.html</anchorfile>
      <anchor>a71f5b02004867942c5309e60c509625d</anchor>
      <arglist>(xmlNode *node, const xmlChar *prop, int *error)</arglist>
    </member>
    <member kind="function">
      <type>long int</type>
      <name>jb_xml_node_get_int_with_default</name>
      <anchorfile>jb__xml_8c.html</anchorfile>
      <anchor>ac594f4ca95700c2fd57c3532848d304d</anchor>
      <arglist>(xmlNode *node, const xmlChar *prop, int *error, long int def)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_xml_node_set_int</name>
      <anchorfile>jb__xml_8c.html</anchorfile>
      <anchor>a62358020fca1bb4c1247d3d921d01323</anchor>
      <arglist>(xmlNode *node, const xmlChar *prop, long int x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_xml_node_set_int_with_default</name>
      <anchorfile>jb__xml_8c.html</anchorfile>
      <anchor>a9651b8cf36ea38b1991e7af00e2f5833</anchor>
      <arglist>(xmlNode *node, const xmlChar *prop, long int x, long int def)</arglist>
    </member>
    <member kind="function">
      <type>JBDOUBLE</type>
      <name>jb_xml_node_get_time</name>
      <anchorfile>jb__xml_8c.html</anchorfile>
      <anchor>ad89a180482082f4d7c9de3f5c1620eb5</anchor>
      <arglist>(xmlNode *node, const xmlChar *prop, int *error)</arglist>
    </member>
    <member kind="function">
      <type>JBDOUBLE</type>
      <name>jb_xml_node_get_time_with_default</name>
      <anchorfile>jb__xml_8c.html</anchorfile>
      <anchor>a9ad2f11e369c63001fbe66bc5fa6dfc2</anchor>
      <arglist>(xmlNode *node, const xmlChar *prop, int *error, JBDOUBLE def)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_xml_node_set_time</name>
      <anchorfile>jb__xml_8c.html</anchorfile>
      <anchor>a3e1c41de66cb9d6996799f1731515928</anchor>
      <arglist>(xmlNode *node, const xmlChar *prop, JBDOUBLE t)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_xml_node_set_time_with_default</name>
      <anchorfile>jb__xml_8c.html</anchorfile>
      <anchor>a2f088b2ae9393771e336c24898a1877f</anchor>
      <arglist>(xmlNode *node, const xmlChar *prop, JBDOUBLE t, JBDOUBLE def)</arglist>
    </member>
    <member kind="function">
      <type>FILE *</type>
      <name>jb_xml_node_get_content_file</name>
      <anchorfile>jb__xml_8c.html</anchorfile>
      <anchor>a08c937fe801b7c6e7c7e81345b6c4be8</anchor>
      <arglist>(xmlNode *node, char **buffer)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_xml_node_set_content_file</name>
      <anchorfile>jb__xml_8c.html</anchorfile>
      <anchor>a0b2b53afa0995bda8330f0c59ee8c924</anchor>
      <arglist>(xmlNode *node, FILE *file)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>jb_xml.h</name>
    <path>/home/burguete/programas/jb/2.0.0/</path>
    <filename>jb__xml_8h.html</filename>
    <includes id="jb__math_8h" name="jb_math.h" local="yes" imported="no">jb_math.h</includes>
    <member kind="function">
      <type>JBDOUBLE</type>
      <name>jb_xml_node_get_float</name>
      <anchorfile>jb__xml_8h.html</anchorfile>
      <anchor>a106bf804777fb8b74439248e14c29d3b</anchor>
      <arglist>(xmlNode *, const xmlChar *, int *)</arglist>
    </member>
    <member kind="function">
      <type>JBDOUBLE</type>
      <name>jb_xml_node_get_float_with_default</name>
      <anchorfile>jb__xml_8h.html</anchorfile>
      <anchor>a069805a00247afe2ec59e10879083caa</anchor>
      <arglist>(xmlNode *, const xmlChar *, int *, JBDOUBLE)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_xml_node_set_float_with_format</name>
      <anchorfile>jb__xml_8h.html</anchorfile>
      <anchor>a79903006c9d4a1063fc720d0d87829bf</anchor>
      <arglist>(xmlNode *, const xmlChar *, char *, JBDOUBLE)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_xml_node_set_float</name>
      <anchorfile>jb__xml_8h.html</anchorfile>
      <anchor>ab8a00819d6f8a8e3dbcfb6f24c265424</anchor>
      <arglist>(xmlNode *, const xmlChar *, JBDOUBLE)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_xml_node_set_float_with_default</name>
      <anchorfile>jb__xml_8h.html</anchorfile>
      <anchor>a63af32579a557b025e71d9f2cf0424fc</anchor>
      <arglist>(xmlNode *, const xmlChar *, JBDOUBLE, JBDOUBLE)</arglist>
    </member>
    <member kind="function">
      <type>long int</type>
      <name>jb_xml_node_get_int</name>
      <anchorfile>jb__xml_8h.html</anchorfile>
      <anchor>a9af956598d223d7c787072264c089eaf</anchor>
      <arglist>(xmlNode *, const xmlChar *, int *)</arglist>
    </member>
    <member kind="function">
      <type>long int</type>
      <name>jb_xml_node_get_int_with_default</name>
      <anchorfile>jb__xml_8h.html</anchorfile>
      <anchor>ae1e514657e852bb9faee8588b5e6f80f</anchor>
      <arglist>(xmlNode *, const xmlChar *, int *, long int)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_xml_node_set_int</name>
      <anchorfile>jb__xml_8h.html</anchorfile>
      <anchor>a19b8628b00973074bdfcce54903266c8</anchor>
      <arglist>(xmlNode *, const xmlChar *, long int)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_xml_node_set_int_with_default</name>
      <anchorfile>jb__xml_8h.html</anchorfile>
      <anchor>a437e7e15216c6717158b10bfdf5649ca</anchor>
      <arglist>(xmlNode *, const xmlChar *, long int, long int)</arglist>
    </member>
    <member kind="function">
      <type>JBDOUBLE</type>
      <name>jb_xml_node_get_time</name>
      <anchorfile>jb__xml_8h.html</anchorfile>
      <anchor>a3b23310a47b8405ac35f1a8e60b749a1</anchor>
      <arglist>(xmlNode *, const xmlChar *, int *)</arglist>
    </member>
    <member kind="function">
      <type>JBDOUBLE</type>
      <name>jb_xml_node_get_time_with_default</name>
      <anchorfile>jb__xml_8h.html</anchorfile>
      <anchor>a9d7456d2fd7d4c27b13bab8b3ed4832c</anchor>
      <arglist>(xmlNode *, const xmlChar *, int *, JBDOUBLE)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_xml_node_set_time</name>
      <anchorfile>jb__xml_8h.html</anchorfile>
      <anchor>a8cb904f4edbe4546b74701683163eadc</anchor>
      <arglist>(xmlNode *, const xmlChar *, JBDOUBLE)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_xml_node_set_time_with_default</name>
      <anchorfile>jb__xml_8h.html</anchorfile>
      <anchor>a391725dbaeac81c835d0945dd1296df5</anchor>
      <arglist>(xmlNode *, const xmlChar *, JBDOUBLE, JBDOUBLE)</arglist>
    </member>
    <member kind="function">
      <type>FILE *</type>
      <name>jb_xml_node_get_content_file</name>
      <anchorfile>jb__xml_8h.html</anchorfile>
      <anchor>a42593d8c1d9465765b535143652a483c</anchor>
      <arglist>(xmlNode *, char **)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>jb_xml_node_set_content_file</name>
      <anchorfile>jb__xml_8h.html</anchorfile>
      <anchor>ad9b1b582b9d3763e5cba08c2b3bfa401</anchor>
      <arglist>(xmlNode *, FILE *)</arglist>
    </member>
  </compound>
</tagfile>
