import { chromium } from 'playwright';

(async () => {
 const browser = await chromium.launch({ headless: false });
 const context = await browser.newContext();
 const page = await context.newPage();
 const numProximosDias = 0;

 // Función de retardo
 const delay = (ms) => new Promise(resolve => setTimeout(resolve, ms));

 // Bloque 1: Navegar a la página
 await page.goto('https://www.cinesa.es/cines/zubiarte/', { waitUntil: 'domcontentloaded' });
 console.log('Página cargada.');
 await delay(2000); // Espera 2 segundos

 // Bloque 2: Rechazar cookies
 const rechazarCookies = async () => {
  const cookiesSelector = 'button#onetrust-reject-all-handler';
  await page.waitForSelector(cookiesSelector, { timeout: 10000 });
  await page.click(cookiesSelector, { force: true });
  console.log('Cookies rechazadas.');
 };
 await rechazarCookies();
 await delay(2000);

 // Bloque 3: Seleccionar la fecha adecuada
 const seleccionarFecha = async () => {
  const targetDataGslide = numProximosDias.toString();
  const dateSelector = `li.v-date-picker-date[data-gslide="${targetDataGslide}"] button.v-date-picker-date__button`;
  await page.waitForSelector(dateSelector, { timeout: 15000 });
  await page.click(dateSelector, { force: true });
  console.log(`✅ Fecha seleccionada: +${numProximosDias} días`);
 };
 await seleccionarFecha();
 await delay(2000);

 // Bloque 4: Clic en el checkbox para mostrar todas las películas
 const clicCheckbox = async () => {
  const checkboxSelector = 'div.v-toggle-input:has(span:has-text("Mostrar todas las películas")) div.v-toggle-input__button';
  await page.waitForSelector(checkboxSelector, { timeout: 30000 });
  await page.click(checkboxSelector, { force: true });
  console.log('Checkbox clickeado.');
 };
 await clicCheckbox();
 await delay(2000);

 // Bloque 5: Esperar a que aparezcan y extraer los títulos
 const extraerTitulos = async () => {
  const titleSelector = 'h2.v-film-title__text';
  await page.waitForSelector(titleSelector, { timeout: 15000 });
  console.log('Títulos detectados.');
  const titles = await page.$$eval(titleSelector, elements =>
      elements.map(el => el.innerText.trim())
  );
  console.log('Películas en cartelera:', titles);
 };
 await extraerTitulos();
// extraer titulos de las peliculas
 c

 // await browser.close();
})();
