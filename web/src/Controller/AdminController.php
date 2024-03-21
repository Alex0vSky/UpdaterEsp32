<?php
namespace App\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Attribute\Route;
use App\Repository\ProductRepository;
use Symfony\Component\HttpFoundation\Request;
use Doctrine\ORM\EntityManagerInterface;
use App\Entity\Product;
use App\Form\ProductType;

class AdminController extends AbstractController {
    #[Route('/', name: 'admin_index')]
    public function indexAction(ProductRepository $repository): Response {
        return $this ->render( 'task/index.html.twig', [
            'all' => $repository ->findAll( ),
        ]);
    }
	
    #[Route('/new', name: 'admin_new_firmware')]
    public function newAction(Request $request, EntityManagerInterface $entityManager): Response {
        $firmware = new Product( );
        $form = $this ->createForm( ProductType::class, $firmware );
        $form ->handleRequest( $request );

        if ( $form ->isSubmitted( ) && $form ->isValid( ) ) {
            $entityManager ->persist( $firmware );
            $entityManager ->flush( );
            return $this ->redirectToRoute( 'admin_index', [], Response::HTTP_SEE_OTHER );
        }

        return $this->render('task/new.html.twig', [
            'form' => $form,
        ]);
    }	

    #[Route('/delete', name: 'admin_delete_firmware')]
    public function deleteAction(Request $request, ProductRepository $repository, EntityManagerInterface $entityManager): Response {
		$firmware = $repository ->findOneBy( ['id' =>$request ->get( 'id' ) ] );
		$entityManager ->remove( $firmware );
		$entityManager ->flush( );
		$this ->addFlash( 'success', 'Removed "' .  $firmware ->getImageName( ) . '"' );
		return $this ->redirectToRoute( 'admin_index', [], Response::HTTP_SEE_OTHER );
    }	
}
