using System;

namespace AutoBolts
{
	using Inventor;	
	using System.Runtime.InteropServices;
	using System.Windows.Forms;
	using System.Collections;

	internal class HoleInfo
	{
		public Matrix Position;
		public double Radius;
		public EdgeProxy Edge;
	}

	public class BoltPlacer
	{		
		private Inventor.Application		m_InventorApplication;
		private Inventor.AssemblyDocument	m_AssemblyDocument;
		private ArrayList					m_CompOccurrenceArray = new ArrayList();
		private ArrayList					m_HoleInfoArray = new ArrayList();
		private string						m_LibraryPath;
		private TreeView                    m_tree;
		
		public string LibaryPath
		{
			set
			{
				m_LibraryPath = value;
			}
		}

		public BoltPlacer()
		{				
		}

		private bool ConnectInventor()
		{	
			try
			{
				try
				{
					// Get active inventor object
					m_InventorApplication = MarshalCore.GetActiveObject( "Inventor.Application" ) as Inventor.Application;
				}
				catch( COMException )
				{
					MessageBox.Show( "AutoBolts : Inventor must be running." );
					return false;
				}

				// Make sure that at least one document is opened
				m_AssemblyDocument = m_InventorApplication.ActiveDocument as AssemblyDocument;
				if( m_AssemblyDocument==null)
				{
					MessageBox.Show( "AutoBolts : An assembly document must be active." );
					return false; 
				}				
			}
			catch( Exception e )
			{
				MessageBox.Show( e.Message );
				return false;
			}

			return true;
		}

		public bool Init(TreeView tree)
		{
			if( !ConnectInventor() )
				return false;

			m_tree = tree;

			ComponentOccurrences CompOccurrences;
			
			try
			{
				AssemblyComponentDefinition AsmCompDefinition;	
				AsmCompDefinition = m_AssemblyDocument.ComponentDefinition;
				CompOccurrences = AsmCompDefinition.Occurrences;
			}
			catch( Exception )
			{
				return false;
			}

			int Index = 0;	
			
			if( !BuildTree( CompOccurrences, ref Index, null ) )
				return false;

			m_tree.ExpandAll();
			return true;
		}

		public bool CanPlaceBolts( int index )
		{
			// If selected node is a Assembly, return false
			if( m_CompOccurrenceArray[index]==null )
				return false;
			else
				return true;
		}

		public void ExecutePlaceBolts(int index)
		{			
			ComponentOccurrence CompOccurrence = m_CompOccurrenceArray[index] as ComponentOccurrence;	
			int HoleInfoCount = 0;

			// Call the function that examines the B-Rep and finds the holes.
			if( !GetHoleInfo( ref m_HoleInfoArray, ref HoleInfoCount, CompOccurrence ) )
				return;

			// Call the function to place the bolts using the previously obtained hole information.
			PlaceBolts( m_HoleInfoArray, HoleInfoCount, m_AssemblyDocument );
		}

		private bool BuildTree( ComponentOccurrences CompOccurrences, ref int Index, TreeNode ParentNode )
		{	
			try
			{
				// Iterate through the ocurrences.
				for( int i=1; i<=CompOccurrences.Count; i++ )
				{	
					Index++;
					ComponentOccurrence CompOccurrence = CompOccurrences[i];
		
					// Get the name of the occurrence.
					string OccurrenceName;
					OccurrenceName = CompOccurrence.Name;

					// Use the Count property of the SubOccurrences property to determine if it's a subassembly or not.
					ComponentOccurrences SubOccurrences = CompOccurrence.SubOccurrences as ComponentOccurrences;
					int SubOccurrencesCount = SubOccurrences.Count;

					if( SubOccurrencesCount>0 )
					{
						// It's a subassembly						
						m_CompOccurrenceArray.Insert( Index-1, null );
						TreeNode node = new TreeNode( OccurrenceName, 1, 1 );
						node.Tag = Index-1;
						
						if (ParentNode == null)
							m_tree.Nodes.Add(node);
						else 
							ParentNode.Nodes.Add( node );
												
						BuildTree(SubOccurrences, ref Index, node );
					}
					else
					{
						// It's not a subassembly						
						m_CompOccurrenceArray.Insert( Index-1, CompOccurrence );
						TreeNode node = new TreeNode( OccurrenceName, 0, 0 );
						node.Tag = Index-1;
						
						if (ParentNode == null)
							m_tree.Nodes.Add(node);
						else 
							ParentNode.Nodes.Add( node );
					}

				}
			}
			catch( COMException e )
			{
				MessageBox.Show( e.Message );
				return false;
			}

			return true;
		}

		private bool GetHoleInfo( ref ArrayList HoleInfoArr, ref int HoleInfoCount, ComponentOccurrence Occurrence ) 
		{
			try
			{
				// Get the surface body of the first occurrence in the assembly
				SurfaceBody SurfaceBody = Occurrence.SurfaceBodies[1];

				// Iterate through loops of the body looking for loops containing
				// single circular edges that connects a cylinder to a face that
				// contains more than one loop.
				Faces faces = SurfaceBody.Faces;
				Face  face;
				for( int i=1; i<=faces.Count; i++ )
				{
					face = faces[i];
					if( face.SurfaceType != SurfaceTypeEnum.kPlaneSurface )
						continue;

					EdgeLoops edgeLoops = face.EdgeLoops;
					EdgeLoop edgeLoop;
					for( int j=1; j<=edgeLoops.Count; j++ )
					{
						edgeLoop = edgeLoops[j];

						// Check to see if the loop contains a single edge.
						if( 1==edgeLoop.Edges.Count && CurveTypeEnum.kCircleCurve==edgeLoop.Edges[1].CurveType )
						{
							Edge edge = edgeLoop.Edges[1];
							Face cylinderFace = null;
							Face planeFace = null;
					
							SurfaceTypeEnum enumSurfaceType = edge.Faces[1].SurfaceType;
							if( enumSurfaceType==SurfaceTypeEnum.kCylinderSurface )
								cylinderFace = edge.Faces[1];
							else if( enumSurfaceType==SurfaceTypeEnum.kPlaneSurface )
								planeFace = edge.Faces[1];
					
							enumSurfaceType = edge.Faces[2].SurfaceType;
							if( enumSurfaceType==SurfaceTypeEnum.kCylinderSurface )
								cylinderFace = edge.Faces[2];
							else if( enumSurfaceType==SurfaceTypeEnum.kPlaneSurface )
								planeFace = edge.Faces[2];

							if( cylinderFace!=null && planeFace!=null )
							{
								// Check that the planar face has multiple loops.  This should
								// eliminate the bottom of holes.					
								if( planeFace.EdgeLoops.Count>1 )
								{
									// Check to see if the cylinder is perpendicular to the plane.
									Plane plane = planeFace.get_Surface( SurfaceTypeEnum.kPlaneSurface) as Plane;
									Cylinder cylinder = cylinderFace.get_Surface( SurfaceTypeEnum.kCylinderSurface ) as Cylinder;
									if( plane.Normal.IsParallelTo( cylinder.AxisVector, 0.001 ) )
									{
										HoleInfoCount++;
										HoleInfo holeInfoNode = new HoleInfo();

										// Save the edge.
										holeInfoNode.Edge = edge as EdgeProxy;
										Circle circle = edge.get_Curve( edge.CurveType ) as Circle;
								
										// Save the radius.
										holeInfoNode.Radius = circle.Radius;
										Matrix matrix = m_InventorApplication.TransientGeometry.CreateMatrix();
										matrix.set_Cell( 1, 4, circle.Center.X );
										matrix.set_Cell( 2, 4, circle.Center.Y );
										matrix.set_Cell( 3, 4, circle.Center.Z );

                                        // Get a normal from the face.
                                        double[] normal = new double[3];
                                        double[] tangent = new double[3];
                                        double[] param = new double[2];
                                        param.SetValue(planeFace.Evaluator.ParamRangeRect.MinPoint.X, 0);
                                        param.SetValue(planeFace.Evaluator.ParamRangeRect.MinPoint.Y, 1);

                                        planeFace.Evaluator.GetNormal(ref param, ref normal);
                                        planeFace.Evaluator.GetTangents(ref param, ref tangent, ref tangent);

                                        matrix.set_Cell(1, 3, normal[0]);
                                        matrix.set_Cell(2, 3, normal[1]);
                                        matrix.set_Cell(3, 3, normal[2]);

                                        matrix.set_Cell(1, 1, tangent[0]);
                                        matrix.set_Cell(2, 1, tangent[1]);
                                        matrix.set_Cell(3, 1, tangent[2]);

                                        matrix.set_Cell(1, 2, normal[1] * tangent[2] - normal[2] * tangent[1]);
                                        matrix.set_Cell(2, 2, normal[2] * tangent[0] - normal[0] * tangent[2]);
                                        matrix.set_Cell(3, 2, normal[0] * tangent[1] - normal[1] * tangent[0]);
								
										holeInfoNode.Position = matrix;
										HoleInfoArr.Insert( HoleInfoCount-1, holeInfoNode );
									}
								}
							}
						}
					}
				}
			}
			catch( Exception e )
			{
				MessageBox.Show( e.Message );
				return false;
			}

			return true;
		}

		void PlaceBolts(ArrayList HoleInfoArr, long HoleInfoCount, AssemblyDocument AsmDoc)
		{
			// Create the bolt library directory if it does not exist.
			if (!System.IO.Directory.Exists(m_LibraryPath))
				System.IO.Directory.CreateDirectory(m_LibraryPath);

			try
			{
				ComponentOccurrences oComponentOccurrences = AsmDoc.ComponentDefinition.Occurrences;
				for( int i = 0; i<HoleInfoCount ; i++)
				{
					string strFileName;
					HoleInfo holeInfo = HoleInfoArr[i] as HoleInfo;
					strFileName = string.Format( "Bolt_{0:F3}.ipt", holeInfo.Radius );

					// Check to see if a bolt this size exists in the library directory.
					string strFilePath = m_LibraryPath + "\\" + strFileName;
					if( !System.IO.File.Exists(strFilePath) )
					{
						// Create a new bolt file of the correct size.
						// Open the seed bolt file.  (Can be opened invisibly by seeting the second
						// argument to False.  This leaves it visible to you can see what's happening.)
						PartDocument oPartDoc;	
						string Path = System.IO.Directory.GetCurrentDirectory() + "\\..\\..\\..\\..\\..\\..\\Data_Files\\BoltSeed.ipt";
						
						oPartDoc = m_InventorApplication.Documents.Open( Path , true ) as PartDocument;

						// Obtain a reference to the parameter called "Diameter".
						ModelParameter DiamParam= oPartDoc.ComponentDefinition.Parameters.ModelParameters["Diameter"];
							
						// Change the value of parameter, rounding it to 3 decimal places.
						DiamParam.Value = holeInfo.Radius * 2;

						// Update the part.
						oPartDoc.Update();
						
						// Save the file the new filename.
						oPartDoc.SaveAs( strFilePath, true );

						// Close the seed bolt file without saving.
						oPartDoc.Close( true );
					}
					
					// Place the bolt using the matrix that was defined previously.
					ComponentOccurrence oBoltOccurrence = oComponentOccurrences.Add( strFilePath, holeInfo.Position );

					// Get the edge of the bolt to use for the constraint.
					EdgeProxy oEdgeProxy = null;
					GetBoltEdge( oBoltOccurrence, ref oEdgeProxy );

					if( oEdgeProxy!=null )
					{
						InsertConstraint oInsertConstraint;
						oInsertConstraint = AsmDoc.ComponentDefinition.Constraints.AddInsertConstraint( oEdgeProxy, holeInfo.Edge, true, 0 , Type.Missing, Type.Missing );
					}
				}
			}
			catch( Exception e )
			{
				MessageBox.Show( e.Message );
				return ;
			}
		}

		private void GetBoltEdge( ComponentOccurrence oCompOcc, ref EdgeProxy oEdgePro )
		{
			try
			{
				// Obtain the document the bolt occurrence references.
				PartDocument oPartDoc = oCompOcc.Definition.Document as PartDocument;

				ObjectCollection oEdges = oPartDoc.AttributeManager.FindObjects( "AutoBolts", "*", Type.Missing);
				if( oEdges.Count==1 )
				{
					// The edge obtained is in the context of the part document.
					// Now get the edge in the context of this particular occurrence.	
					Object temp;
					oCompOcc.CreateGeometryProxy( oEdges[1], out temp );
					oEdgePro = temp as EdgeProxy;
				}
			}
			catch( Exception e )
			{
				MessageBox.Show( e.Message );
			}
		}

	}
}
