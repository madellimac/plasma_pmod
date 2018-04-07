---------------------------------------------------------------------
-- TITLE: UART
-- AUTHOR: Camille Monière (CamilleMVDD@gmail.com)
-- DATE CREATED: 2018/04/07
-- FILENAME: uart_pmod.vhd
-- PROJECT: Plasma CPU core
-- COPYRIGHT: Software placed into the public domain by the author.
--    Software 'as is' without warranty.  Author liable for nothing.  
--    Integrated files (uart_recv and uart_send ) belongs to Yannick Bornat, all rights reserved.
--    
-- DESCRIPTION:
--    Implements the UART for pmod junctions. Uses files designed and written by Yannick Bornat.
---------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_misc.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_textio.all;
use ieee.std_logic_unsigned.all;


entity uart_pmod is
   port(
        clk          : in  std_logic;
        reset        : in  std_logic;
        enable_read  : in  std_logic;
        enable_write : in  std_logic;
        data_in      : in  std_logic_vector(7 downto 0);
        data_out     : out std_logic_vector(7 downto 0);
        uart_read    : in  std_logic;
        uart_write   : out std_logic;
        busy_write   : out std_logic;
        data_avail   : out std_logic);
end; --entity uart_pmod

architecture logic of uart_pmod is

   signal reg_debug       : std_logic_vector(7 downto 0);
   
   component UART_recv 
      Port ( 
             clk    : in  STD_LOGIC;
             reset  : in  STD_LOGIC;
             rx     : in  STD_LOGIC;
             dat    : out STD_LOGIC_VECTOR (7 downto 0);
             dat_en : out STD_LOGIC);
   end component;
   
   component UART_send 
      Port ( 
             clk    : in  STD_LOGIC;
             reset  : in  STD_LOGIC;
             dat_en : in  STD_LOGIC;
             dat    : in  STD_LOGIC_VECTOR (7 downto 0);
             TX     : out STD_LOGIC;
             busy   : out STD_LOGIC);
   end component;
   
begin

unit_recv : UART_recv port map( clk     => clk,
                                reset   => reset,
                                rx      => uart_read,
                                dat     => data_out,
                                dat_en  => data_avail
                              );           
                                                  
unit_send : UART_send port map( clk     => clk,
                                reset   => reset,
                                dat_en  => enable_write,
                                dat     => data_in,
                                TX      => uart_write,
                                busy    => busy_write
                              );

end; --architecture logic
